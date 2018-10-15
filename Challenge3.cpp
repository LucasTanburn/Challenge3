#include <iostream>
#include <math.h>

using namespace std;

class Point2D
{
    public:
        int x;
        int y;
};

void PrintPoint2D(Point2D n)
{
    cout << '(' << n.x << ',' << n.y << ')' << endl;
}

float Distance(Point2D coord1, Point2D coord2)
{
    return sqrt(pow((coord1.x - coord2.x),2) + pow((coord1.y - coord2.y),2));
}

void Point2DSort (Point2D arr[], int size)
{
    Point2D origin;
    origin.x = 0;
    origin.y = 0;

    for (int i = 0; i < size-1; i++)
    {
        bool didswap = false;

        for (int j = 0; j < size-i-1; j++)
        {
            if (Distance(arr[j],origin) > Distance (arr[j+1],origin))
            {
                swap(arr[j],arr[j+1]);
                didswap = true;
            }
        }
        if (!didswap) break;
    }
}

string Point2DAngle (Point2D coord1, Point2D coord2, Point2D coord3)
{
    float twiceSignedArea = (coord2.x - coord1.x)*(coord3.y - coord1.y) - (coord2.y - coord1.y)*(coord3.x - coord1.x);

    if (twiceSignedArea > 0) return "anti-clockwise";
    else if (twiceSignedArea < 0) return "clockwise";
    else if (twiceSignedArea == 0) return "collinear";
}

bool Point2DIntersect(Point2D A1, Point2D A2, Point2D B1, Point2D B2)
{
    Point2D origin;
    origin.x = 0;
    origin.y = 0;

    if ((Point2DAngle(A1,A2,B1) != Point2DAngle(A1,A2,B2)) && (Point2DAngle(B1,B2,A1) != Point2DAngle(B1,B2,A2))) return true; // This checks that the type of angle is not the same for both lines
    if ((Point2DAngle(A1,A2,B1) == "collinear" && Point2DAngle(A1,A2,B2) == "collinear") && max(Distance(B1,origin),Distance(B2,origin)) > min(Distance(A1,origin),Distance(A2,origin))) return true; // These lines catch cases where a line or point lies on the same line
    if ((Point2DAngle(B1,B2,A1) == "collinear" && Point2DAngle(B1,B2,A2) == "collinear") && max(Distance(B1,origin),Distance(B2,origin)) > min(Distance(A1,origin),Distance(A2,origin))) return true;

    else return false;
}

bool PolygonContain(Point2D polygon[], Point2D point, int nsides)
{
    int xmax = polygon[0].x, xmin = polygon[0].x;

    for (int i = 1; i < nsides; i++)
    {
        if (polygon[i].x > xmax) xmax = polygon[i].x;
        if (polygon[i].x < xmin) xmin = polygon[i].x;
    }

    int polylength = xmax - xmin;
    if (polylength == 1) return false;

    Point2D lineleft, lineright;

    lineleft.x = point.x - polylength;
    lineleft.y = point.y;
    lineright.x = point.x + polylength;
    lineright.y = point.y;

    int intersectcount = 0;

    for (int i = 0; i < nsides; i++)
    {
        int nsideloop = i+1;

        if (nsideloop > nsides-1) nsideloop -= nsides;
        if (Point2DAngle(polygon[i], lineleft, polygon[nsideloop]) == "collinear" || Point2DAngle(polygon[i], lineleft, polygon[nsideloop]) == "collinear") return false;
        if (Point2DIntersect(lineleft, lineright, polygon[i], polygon[nsideloop])) intersectcount++;
    }

    if (intersectcount%2 == 1 || intersectcount == 0) return false; // If the line does not intersect with the boundaries or intersects an odd number of times it is outside
    else if (intersectcount%2 == 0) return true; // If the line intersects an even number of times it is inside
}

int main()
{
    cout << "Question 1 test:" << endl;

    Point2D coord1, coord2;
    coord1.x = 0;
    coord1.y = 0;
    coord2.x = 3;
    coord2.y = 4;

    cout << "Point 1:" << endl;
    PrintPoint2D(coord1);
    cout << "Point 2:" << endl;
    PrintPoint2D(coord2);
    cout << "Distance:\n" << Distance(coord1, coord2) << endl;
    cout << endl;


    cout << "Question 2 test:" << endl;

    Point2D pointarray[5];
    pointarray[0].x = 5; pointarray[0].y = 5;
    pointarray[1].x = 1; pointarray[1].y = 0;
    pointarray[2].x = 16; pointarray[2].y = 30;
    pointarray[3].x = 2; pointarray[3].y = 1;
    pointarray[4].x = 0; pointarray[4].y = 0;

    cout << "Unsorted array:" << endl;

    for (int i = 0; i < 5; i++)
    {
        PrintPoint2D(pointarray[i]);
    }

    Point2DSort(pointarray, 5);

    cout << "Sorted array:" << endl;

    for (int i = 0; i < 5; i++)
    {
        PrintPoint2D(pointarray[i]);
    }

    cout << endl;


    cout << "Question 3 test:" << endl;

    Point2D fixed1, fixed2, clock, anti, colin;
    fixed1.x = 3; fixed1.y = 5;
    fixed2.x = 3; fixed2.y = 3;
    clock.x = 5; clock.y = 1;
    anti.x = 1; anti.y = 1;
    colin.x = 3; colin.y = 1;

    cout << "Clockwise angle:\n" << Point2DAngle(fixed1, fixed2, clock) << endl;
    cout << "Anti-clockwise angle:\n" << Point2DAngle(fixed1, fixed2, anti) << endl;
    cout << "Colinear angle:\n" << Point2DAngle(fixed1, fixed2, colin) << endl;
    cout << endl;


    cout << "Question 4 test:" << endl;

    Point2D FA1, FA2, FB1, FB2;
    FA1.x = 2; FA1.y = 2;
    FA2.x = 2; FA2.y = 4;
    FB1.x = 4; FB1.y = 2;
    FB2.x = 4; FB2.y = 4;

    Point2D TA1, TA2, TB1, TB2;
    TA1.x = 2; TA1.y = 2;
    TA2.x = 4; TA2.y = 4;
    TB1.x = 4; TB1.y = 2;
    TB2.x = 2; TB2.y = 4;

    Point2D CA1, CA2, CB1, CB2;
    CA1.x = 2; CA1.y = 2;
    CA2.x = 4; CA2.y = 4;
    CB1.x = 1; CB1.y = 1;
    CB2.x = 3; CB2.y = 3;

    cout << "Set 1 - Non-intersecting:\n" << Point2DIntersect(FA1, FA2, FB1, FB2) << endl;
    cout << "Set 2  - Intersecting:\n" << Point2DIntersect(TA1, TA2, TB1, TB2) << endl;
    cout << "Set 3  - Collinear:\n" << Point2DIntersect(CA1, CA2, CB1, CB2) << endl;
    cout << endl;


    cout << "Question 5 test:" << endl;

    Point2D square[4], inpoint, outpoint;
    square[0].x = 1; square[0].y = 1;
    square[1].x = 3; square[1].y = 1;
    square[2].x = 3; square[2].y = 3;
    square[3].x = 1; square[3].y = 3;

    inpoint.x = 2; inpoint.y = 2;
    outpoint.x = 3; outpoint.y = 2;

    cout << "Point 1 is inside:\n" << PolygonContain(square, inpoint, 4) << endl;
    cout << "Point 2 is outside:\n" << PolygonContain(square, outpoint, 4) << endl;
}
