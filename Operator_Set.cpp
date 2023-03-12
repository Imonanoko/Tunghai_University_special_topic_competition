#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> S_Box = {52, 91, 130, 169, 208, 247, 30, 71, 112, 153, 194, 235, 20, 63, 106, 149, 192, 236, 23, 68, 114, 159, 204, 250, 39, 86, 134, 181, 228, 19, 70, 120, 170, 219, 12, 64, 117, 168, 221, 16, 73, 126, 180, 234, 34, 90, 146, 203, 4, 61, 123, 183, 242, 45, 105, 167, 230, 37, 100, 164, 229, 40, 104, 174, 241, 51, 122, 191, 5, 78, 148, 220, 38, 113, 189, 8, 85, 162, 244, 65, 144, 225, 53, 137, 217, 48, 136, 222, 55, 143, 237, 72, 161, 0, 95, 193, 29, 131, 231, 77, 178, 24, 129, 239, 88, 198, 49, 163, 18, 138, 254, 111, 233, 98, 216, 92, 213, 89, 215, 97, 232, 110, 253, 135, 21, 166, 56, 202, 101, 2, 156, 58, 214, 128, 36, 206, 125, 43, 223, 151, 76, 10, 197, 141, 80, 26, 238, 184, 142, 99, 62, 32, 9, 248, 218, 205, 196, 190, 195, 201, 212, 246, 11, 41, 75, 116, 160, 224, 31, 102, 175, 14, 107, 200, 66, 177, 59, 187, 93, 3, 165, 96, 42, 252, 207, 176, 171, 173, 199, 251, 44, 109, 186, 54, 158, 79, 1, 179, 140, 132, 147, 209, 25, 119, 17, 182, 133, 127, 172, 22, 139, 74, 60, 94, 227, 118, 108, 188, 81, 67, 154, 84, 152, 69, 150, 103, 6, 46, 50, 35, 28, 47, 145, 57, 157, 226, 7, 240, 87, 83, 82, 13, 210, 121, 15, 33, 27, 245, 211, 124, 115, 155, 185, 243, 249, 255};
int Inverse_S_Box(int Value)
{
    vector<int>::iterator it = find(S_Box.begin(), S_Box.end(), Value);
    int index = std::distance(S_Box.begin(), it);
    return index;
}
vector<int> BinaryAdd(vector<int> n1, vector<int> n2)
{
    vector<int> n3(8);
    int cy = 0;
    for (int i = 7; i >= 0; i--)
    {
        int sum = n1[i] + n2[i] + cy;
        cy = sum >> 8;
        int index = sum % 256;
        n3[i] = S_Box[index] ;
    }
    return n3;
}
vector<int> BinarySub(vector<int> n3, vector<int> n2)
{
    vector<int> n1(8);
    int br = 0;
    for (int i = 7; i >= 0; i--)
    {
        int sub = Inverse_S_Box(n3[i]) - n2[i] - br;
        if (sub < 0)
        {
            br = 1;
        }
        else
        {
            br = 0;
        }
        n1[i] = sub + (br << 8);
    }
    return n1;
}
vector<int> Rotate(vector<int> n1, vector<int> n2)
{
    vector<int> Rotaten3(8);
    int save0=n1.at(0);
    int save1=n1.at(1);
    for(int i=2;i<8;i++){
        n1.at(i-2)=n1.at(i);
    }
    n1.at(6)=save0;
    n1.at(7)=save1;
    for (int i = 0; i < 8; i++)
    {
        int a = (n1.at(i) ^ n2.at(i)) ^ 0b11111111;
        Rotaten3.at(i)= a;
    }
    return Rotaten3;
}
vector<int> InverseRotate(vector<int> n3, vector<int> n2)
{
    vector<int> InverseRotaten1(8);
    for (int i = 0; i < 8; i++)
    {
        int a = (n3[i] ^ n2[i]) ^ 0b11111111;
        InverseRotaten1[i] = a;
    }
    int save6=InverseRotaten1[6],save7=InverseRotaten1[7];
    for(int i = 5;i>=0;i--){
        InverseRotaten1[i+2]=InverseRotaten1[i];
    }
    InverseRotaten1[0]=save6;
    InverseRotaten1[1]=save7;
    return InverseRotaten1;
}

int main(void)
{
    vector<int> n1={123,25,123,64,0,28,10,88};
    vector<int> n2={145,200,85,76,12,0,24,55};
    vector<int> Rotaten3=Rotate(n1,n2);
    vector<int> outcome=InverseRotate(Rotaten3,n2);
    for(int i=0;i<8;i++){
        cout<<outcome[i]<<" ";
    }
}
