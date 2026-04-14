#include "itkImage.h"
#include "itkImageFileWriter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkContinuousIndex.h"
#include "itkMatrix.h"
#include "GenerateCirclesCLP.h"

using PixelType           = unsigned char;
using ImageType           = itk::Image<PixelType, 2>;
using WriterType          = itk::ImageFileWriter<ImageType>;
using ContinuousIndexType = itk::ContinuousIndex<double, 2>;

static int GenerateCircleImage(
  const std::vector<double> & spacingVals,
  const std::vector<double> & originVals,
  const std::vector<double> & dirVals,
  const std::vector<int>    & sizeVals,
  const std::vector<double> & centerVals,
  double                      diameterMM,
  const std::string         & nrrdPath,
  const std::string         & pngPath)
{
  const double radiusMM = diameterMM / 2.0;
  auto image = ImageType::New();

  ImageType::SizeType size;
  size[0] = static_cast<itk::SizeValueType>(sizeVals[0]);
  size[1] = static_cast<itk::SizeValueType>(sizeVals[1]);

  ImageType::RegionType region;
  region.SetSize(size);
  image->SetRegions(region);

  ImageType::SpacingType spacing;
  spacing[0] = spacingVals[0];
  spacing[1] = spacingVals[1];
  image->SetSpacing(spacing);

  ImageType::PointType origin;
  origin[0] = originVals[0];
  origin[1] = originVals[1];
  image->SetOrigin(origin);

  itk::Matrix<double, 2, 2> dir;
  dir[0][0] = dirVals[0];  dir[0][1] = dirVals[1];
  dir[1][0] = dirVals[2];  dir[1][1] = dirVals[3];
  image->SetDirection(dir);

  image->Allocate();
  image->FillBuffer(0);

  const double cx = centerVals[0];
  const double cy = centerVals[1];

  itk::ImageRegionIteratorWithIndex<ImageType> it(image, region);
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
  {
    const ImageType::IndexType & idx = it.GetIndex();

    ContinuousIndexType contIdx;
    contIdx[0] = static_cast<double>(idx[0]);
    contIdx[1] = static_cast<double>(idx[1]);

    ImageType::PointType pt;
    image->TransformContinuousIndexToPhysicalPoint(contIdx, pt);

    const double dx = pt[0] - cx;
    const double dy = pt[1] - cy;
    if (std::sqrt(dx * dx + dy * dy) <= radiusMM)
    {
      it.Set(255);
    }
  }

  try
  {
    auto writer = WriterType::New();
    writer->SetInput(image);

    writer->SetFileName(nrrdPath);
    writer->Update();
    std::cout << "Saved NRRD : " << nrrdPath << "\n";

    writer->SetFileName(pngPath);
    writer->Update();
    std::cout << "Saved PNG  : " << pngPath << "\n";
  }
  catch (itk::ExceptionObject & err)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char * argv[])
{
  PARSE_ARGS;

  if (GenerateCircleImage(spacing1, origin1, directionCosines1,
                          sizePixels1, centerMM1, diameterMM1,
                          outputNRRD1, outputPNG1) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (GenerateCircleImage(spacing2, origin2, directionCosines2,
                          sizePixels2, centerMM2, diameterMM2,
                          outputNRRD2, outputPNG2) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}