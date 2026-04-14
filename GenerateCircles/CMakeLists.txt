set(GenerateCircles_SOURCE GenerateCircles.cxx)
GENERATECLP(GenerateCircles_SOURCE GenerateCircles.xml)

add_executable(GenerateCircles_${MYHAWKID} ${GenerateCircles_SOURCE})
target_link_libraries(GenerateCircles_${MYHAWKID} ${ITK_LIBRARIES})