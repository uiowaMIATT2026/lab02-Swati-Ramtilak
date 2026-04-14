set(ResampleImage_SOURCE ResampleImage.cxx)
GENERATECLP(ResampleImage_SOURCE ResampleImage.xml)

add_executable(ResampleImage_${MYHAWKID} ${ResampleImage_SOURCE})
target_link_libraries(ResampleImage_${MYHAWKID} ${ITK_LIBRARIES})
