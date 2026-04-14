#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkIdentityTransform.h"
#include "ResampleImageCLP.h"

int main(int argc, char * argv[])
{
  PARSE_ARGS;

  constexpr unsigned int Dimension = 2;
  using PixelType    = float;
  using ImageType    = itk::Image<PixelType, Dimension>;

  const auto inputImage     = itk::ReadImage<ImageType>(inputImageFile);
  const auto referenceImage = itk::ReadImage<ImageType>(referenceImageFile);
  using TransformType = itk::IdentityTransform<double, Dimension>;
  auto transform = TransformType::New();
  transform->SetIdentity();
  using InterpolatorType = itk::LinearInterpolateImageFunction<ImageType, double>;
  auto interpolator = InterpolatorType::New();

  using ResampleFilterType = itk::ResampleImageFilter<ImageType, ImageType>;
  auto resampler = ResampleFilterType::New();

  resampler->SetInput(inputImage);
  resampler->SetTransform(transform);
  resampler->SetInterpolator(interpolator);

  resampler->SetSize(referenceImage->GetLargestPossibleRegion().GetSize());
  resampler->SetOutputSpacing(referenceImage->GetSpacing());
  resampler->SetOutputOrigin(referenceImage->GetOrigin());
  resampler->SetOutputDirection(referenceImage->GetDirection());
  resampler->SetDefaultPixelValue(static_cast<PixelType>(defaultPixelValue));

  try
  {
    itk::WriteImage(resampler->GetOutput(), outputImageFile);
    std::cout << "Resampled image saved: " << outputImageFile << "\n";

    const auto inSize  = inputImage->GetLargestPossibleRegion().GetSize();
    const auto inSp    = inputImage->GetSpacing();
    const auto refSize = referenceImage->GetLargestPossibleRegion().GetSize();
    const auto refSp   = referenceImage->GetSpacing();

    std::cout << "Input    : " << inSize[0]  << "x" << inSize[1]
              << " px  spacing " << inSp[0]  << "x" << inSp[1]  << " mm/px\n";
    std::cout << "Reference: " << refSize[0] << "x" << refSize[1]
              << " px  spacing " << refSp[0] << "x" << refSp[1] << " mm/px\n";
  }
  catch (const itk::ExceptionObject & err)
  {
    std::cerr << "ExceptionObject caught!\n" << err << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
