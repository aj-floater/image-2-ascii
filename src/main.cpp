#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

Mat crop_image(Mat image){
    Size size = image.size();
    Rect crop_region(0, 0, size.width - (size.width % 8), size.height - (size.height % 14));
    // Rect crop_region(0, 0, 251, 251);
    return image(crop_region);
}

int convert_to_extreme(int data){
    data = data / (14*8);
    return (data > (265/2)) ? 1 : 0;
}

vector<int> retrieve_image_data(Mat image){
    Size size = image.size();
    int x = 0;
    int y = 0;
    int recordX = 0;
    int recordY = 0;
    vector<int> data;

    int b = 0; int g = 0; int r = 0;

    for (int k = 0; k < (size.width / 8) * (size.height / 14); k++)
    {
        for (int j = 0; j < 14; j++){
            for (int i = 0; i < 8; i++){            
                Vec3b color = image.at<Vec3b>(Point(x,y));

                b += color[0];
                g += color[1];
                r += color[2];

                x++;
                if (x == recordX + 8) x -= 8;
            }
            y++;
            if (y == recordY + 14) y -= 14;
        }

        b = convert_to_extreme(b);
        g = convert_to_extreme(g);
        r = convert_to_extreme(r);

        data.push_back(1*b + 2*g + 4*r);

        // cout << (1*b + 2*g + 4*r) << endl;

        x += 8;
        recordX += 8;
        if (x == size.width){
            x = 0;
            recordX = 0;
            y += 14;
            recordY += 14;
        }

        // cout << "x: " + to_string(x) + " y: " + to_string(y) << endl;
    }
    return data;
    // cout << to_string(size.width) + " x " + to_string(size.height) << endl;
}

int main( int argc, char** argv )
{
    if( argc != 2)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    Mat image, image_modified;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    image = crop_image(image);

    vector<int> data = retrieve_image_data(image);

    Size size = image.size();
    ofstream outputFile;
    std::vector<std::string> argList(argv, argv + argc);
    outputFile.open(argList[1].erase(argList[1].size() - 4) + ".asc");
    outputFile << to_string(size.width/8) + "x" + to_string(size.height/14) + "\n";
    for (int d : data){
        outputFile << d;
    }
    outputFile.close();


    // namedWindow( "original image", WINDOW_AUTOSIZE );
    // imshow( "original image", image );

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}