#include <iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct ImageV {
    vector < vector<int>> ImageData;
    int cols, rows, maxGray;
    string ImageFile;
    bool imageLoaded;
    bool imageModified;

    int loadImage(string ImageName) {
        ifstream IN(ImageName);

        if (!IN.is_open())
            return -1;

        cout << "Loading Image from " << ImageName<< endl;

        string MagicNumber, Comment;

        getline(IN, MagicNumber);
        getline(IN, Comment);

        IN >> cols >> rows >> maxGray;

        ImageData = vector<vector<int>>(rows+1, vector<int>(cols+1));

        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++) 
                IN >> ImageData[r][c];

        if (IN.fail())
            return -2;

        IN.close();
        ImageFile = ImageName;
        cout << ImageFile << " " << "Loaded" << endl;
        imageLoaded = true;
        imageModified = false;
        return 0;
    }

    int saveImage() {

        ofstream COUT(ImageFile);
        if (!COUT.is_open())
            return -1;
        cout << "Saving Image in "<<ImageFile << endl;
        COUT << "P2\n# This is a comment\n"
            << cols << " " << rows << endl << maxGray << endl;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++)
                COUT << ImageData[r][c] << " ";
            COUT << endl;
        }
        cout << "Image Saved" << endl;
        COUT.close();
        imageModified = false;
        return 0;
    }

    void horzontalFlip() {

        for (int r = 0; r < rows / 2; r++) {
            for (int c = 0; c < cols; c++) {
                int T = ImageData[r][c];
                ImageData[r][c] = ImageData[rows - r][c];
                ImageData[rows - r][c] = T;
            }
        }
        return;
    }
};
int main() {
    ImageV Img;
    Img.loadImage("C:\\Data\\Img.pgm");
    Img.horzontalFlip();
    Img.saveImage();
    return 0;
}
