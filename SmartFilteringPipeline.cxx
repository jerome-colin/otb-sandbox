#include "itkMacro.h"  // Exception handler
#include "otbCommandLineArgumentParser.h"
#include "otbImage.h"
#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "itkUnaryFunctorImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "otbHarrisImageFilter.h"

int main(int argc, char * argv[])
{
  try
    {
      typedef otb::CommandLineArgumentParser ParserType;
      ParserType::Pointer parser = ParserType::New();

      parser->SetProgramDescription(
				    "This program applies a Harris detector on the input image");
      parser->AddInputImage();
      parser->AddOutputImage();
      parser->AddOption("--SigmaD",
			"Set the sigmaD parameter. Default is 1.0",
			"-d",
			1,
			false);
      parser->AddOption("--SigmaI",
			"Set the sigmaI parameter. Default is 1.0",
			"-i",
			1,
			false);
      parser->AddOption("--Alpha",
			"Set the alpha parameter. Default is 1.0",
			"-a",
			1,
			false);

      typedef otb::CommandLineArgumentParseResult ParserResultType;
      ParserResultType::Pointer parseResult = ParserResultType::New();

      try
	{
	  parser->ParseCommandLine(argc, argv, parseResult);
	}

      catch (itk::ExceptionObject& err)
	{
	  std::string descriptionException = err.GetDescription();
	  if (descriptionException.find("ParseCommandLine(): Help Parser")
	      != std::string::npos)
	    {
	      return EXIT_SUCCESS;
	    }
	  if (descriptionException.find("ParseCommandLine(): Version Parser")
	      != std::string::npos)
	    {
	      return EXIT_SUCCESS;
	    }
	  return EXIT_FAILURE;
	}

      typedef double PixelType;
      typedef otb::Image<PixelType, 2> ImageType;

      typedef unsigned char OutputPixelType;
      typedef otb::Image<OutputPixelType, 2> OutputImageType;

      typedef otb::ImageFileReader<ImageType> ReaderType;
      ReaderType::Pointer reader = ReaderType::New();

      typedef otb::ImageFileWriter<OutputImageType> WriterType;
      WriterType::Pointer writer = WriterType::New();

      reader->SetFileName(parseResult->GetInputImage().c_str());
      writer->SetFileName(parseResult->GetOutputImage().c_str());

      typedef otb::HarrisImageFilter<ImageType, ImageType> FilterType;
      FilterType::Pointer filter = FilterType::New();

      // Set filter parameters from arguments if present
      if (parseResult->IsOptionPresent("--SigmaD"))
	filter->SetSigmaD(
			  parseResult->GetParameterDouble("--SigmaD"));

      if (parseResult->IsOptionPresent("--SigmaI"))
	filter->SetSigmaI(
			  parseResult->GetParameterDouble("--SigmaI"));

      if (parseResult->IsOptionPresent("--Alpha"))
	filter->SetAlpha(
			 parseResult->GetParameterDouble("--Alpha"));

      // Adding a rescaler
      typedef itk::RescaleIntensityImageFilter <ImageType, OutputImageType> RescalerType;
      RescalerType::Pointer rescaler = RescalerType::New();

      rescaler->SetOutputMinimum(0);
      rescaler->SetOutputMaximum(255);

      // Pipeline
      filter->SetInput(reader->GetOutput());
      rescaler->SetInput(filter->GetOutput());
      writer->SetInput(rescaler->GetOutput());

      writer->Update();
	  
    }

  catch (itk::ExceptionObject& err)
    {
      std::cout << "Following otbException catch: " << std::endl;
      std::cout << err << std::endl;
      return EXIT_FAILURE;
    }

  catch (std::bad_alloc& err)
    {
      std::cout << "Exception bad alloc: " << (char*) err.what() << std::endl;
      return EXIT_FAILURE;
    }

  catch (...)
    {
      std::cout << "Unknown Exception found!" << std::endl;
      return EXIT_FAILURE;
    }
  
  return EXIT_SUCCESS;
}
