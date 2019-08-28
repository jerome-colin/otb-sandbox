#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbOrthoRectificationFilter.h"
#include "otbGenericMapProjection.h"
#include "otbSimpleRcsPanSharpeningFusionImageFilter.h"
#include "otbStandardFilterWatcher.h"

int main(int argc, char* argv[])
{
  if (argc != 12)
    {
      std::cout <<
	"Too lazy to manage parsing, please ensure you have 12 arguments" << std::endl;
      return EXIT_FAILURE;
    }

  typedef otb::Image<unsigned int, 2> ImageType;
  typedef otb::VectorImage<unsigned int, 2> VectorImageType;
  typedef otb::Image<double, 2> DoubleImageType;
  typedef otb::VectorImage<double, 2> DoubleVectorImageType;
  typedef otb::ImageFileReader<ImageType> ReaderType;
  typedef otb::ImageFileReader<VectorImageType> VectorReaderType;
  typedef otb::ImageFileWriter<VectorImageType> WriterType;

  ReaderType::Pointer readerPAN = ReaderType::New();
  VectorReaderType::Pointer readerXS = VectorReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  readerPAN->SetFileName(argv[1]);
  readerXS->SetFileName(argv[2]);
  writer->SetFileName(argv[3]);

  typedef otb::GenericMapProjection<otb::TransformDirection::INVERSE> InverseProjectionType;
  InverseProjectionType::Pointer utmMapProjection = InverseProjectionType::New();
  utmMapProjection->SetWkt("Utm");
  utmMapProjection->SetParameter("Zone", argv[4]);
  utmMapProjection->SetParameter("Hemisphere", argv[5]);

  ImageType::IndexType start;
  start[0] = 0;
  start[1] = 0;

  ImageType::SizeType size;
  size[0] = atoi(argv[8]);
  size[1] = atio(argv[9]);

  ImageType::SpacingType spacing;
  spacing[0] = atof(argv[10]);
  spacing[1] = atof(argv[11]);

  ImageType::PointType origin;
  origin[0] = strtod(argv[6], ITK_NULLPTR);
  origin[1] = strtod(argv[7], ITK_NULLPTR);

  typedef otb::OrthoRectificationFilter<ImageType, DoubleImageType,
					InverseProjectionType> OrthoRectifFilterType;
  
}

  
