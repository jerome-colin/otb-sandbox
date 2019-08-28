/** Attempt to use gnuplot, not finished yet...**/

#include "otbImage.h"
#include "otbImageFileReader.h"
#include "itkImageRegionIterator.h"
#include "gnuplot-iostream/gnuplot-iostream.h"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " <input_filename> <output_filename>" << std::endl;
  }

  typedef unsigned char PixelType;
  typedef otb::Image<PixelType, 2> ImageType;
  typedef otb::ImageFileReader<ImageType> ReaderType;
  typedef itk::ImageRegionConstIterator<ImageType> ConstIteratorType;

  ReaderType::Pointer reader = ReaderType::New();

  /**  
  reader->SetFileName(argv[1]);

  filter->SetInput(reader->GetOutput());

  writer->Update();
  **/
  
  return EXIT_SUCCESS;
}
