#include "mirtk/Common.h"
#include "mirtk/Options.h"
#include "mirtk/IOConfig.h"
#include "mirtk/GenericImage.h"

using namespace mirtk;

void NegateMask(GreyImage* img, char* out_img_fn) {
	
	
	for (int i=0;i<img->GetX();i++)
	{
		for (int j=0;j<img->GetY();j++)
		{
			for (int k=0;k<img->GetZ();k++)
			{
				if (img->Get(i,j,k) > 0)
				{
					img->Put(i,j,k, 0);				// negate
				}
				else 
				{
					img->Put(i,j,k, 1);				// negate
				}
			}
		}
	}

	img->Write(out_img_fn);	
	
	
}

int main(int argc, char **argv)
{
	int optind;
	bool foundArgs=false;
			
	GreyImage img1; 
	char* input_f="", *output_f="", *output_txt="";

	if (argc >= 1) 
	{
		int optind=1;
		
		while ((optind < argc) && (argv[optind][0]=='-')) {
			
			string sw = argv[optind];
			
			if (sw == "-i") {
				optind++;
				input_f = argv[optind]; 
				foundArgs = true;	
			}
			
			else if (sw == "-o") {
				optind++;
				output_f = argv[optind]; 
			}

			optind++; 
		}
	}
	
	if (foundArgs == false)
	{
		cout << "\n\nUsage: mirtk evaluate-negate-mask \n\n\t-i binary mask> \n\t-o <output image>" << endl; 
		exit(0); 
	}

	else
	{
		InitializeIOLibrary();
		//GreyImage img1(input_f1);
		//GreyImage img2(input_f2); 

		UniquePtr<BaseImage> img1(BaseImage::New(input_f));
		
		
		NegateMask(new GenericImage<short>(*img1), output_f);
		
	}

}
