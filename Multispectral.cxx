#include "otbImage.h"
#include "otbVectorImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbMultiToMonoChannelExtractROI.h"
#include "itkShiftScaleImageFilter.h"
#include "otbPerBandVectorImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename> <band>" << std::endl;
  }

  // STEP 1: type definitions

  // 2D VectorImage
  typedef unsigned short int PixelType;
  typedef otb::VectorImage <PixelType, 2> VectorImageType;

  // Creating reader
  typedef otb::ImageFileReader <VectorImageType> ReaderType;
  ReaderType::Pointer reader = ReaderType::New();

  // Creating channel extractor
  typedef otb::MultiToMonoChannelExtractROI <PixelType, PixelType> ExtractChannelType;
  ExtractChannelType::Pointer extractChannel = ExtractChannelType::New();

  // Creating a rescaler
  typedef otb::Image <PixelType, 2> ImageType;
  typedef itk::RescaleIntensityImageFilter <ImageType, ImageType> RescaledType;
  RescaledType::Pointer rescaler = RescaledType::New();

  // Creating a writer
  typedef otb::ImageFileWriter <ImageType> WriterType;
  WriterType::Pointer writer = WriterType::New();

  // STEP 2: pipeline
  reader->SetFileName(argv[1]);
  writer->SetFileName(argv[2]);

  reader->UpdateOutputInformation();
  extractChannel->SetExtractionRegion(reader->GetOutput()->GetLargestPossibleRegion());

  extractChannel->SetChannel(1);
  extractChannel->SetInput(reader->GetOutput());
  
  rescaler->SetInput(extractChannel->GetOutput());

  writer->SetInput(rescaler->GetOutput());
  writer->Update();
  
  return EXIT_SUCCESS;
}
