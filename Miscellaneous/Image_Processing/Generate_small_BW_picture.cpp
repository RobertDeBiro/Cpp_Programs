#include <iostream>
#include <vector>
#include <array>
#include <fstream>

const int width = 4;
const int height = 4;
const int pixel_size = 1;
const long pixel_amount = (width / pixel_size) * (height / pixel_size);
const int overflow = width + 1;

struct Position
{
	double x;
	double y;
};

// Given three collinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Position p, Position q, Position r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Position p, Position q, Position r)
{
	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0.0) return 0; // collinear
	return (val > 00.0) ? 1 : 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1' and 'p2q2' intersect.
bool doIntersect(Position p1, Position q1, Position p2, Position q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool isInside(Position polygon[], int n, Position p)
{
	// There must be at least 3 vertices in polygon[]
	if (n < 3) return false;

	// Create a point for line segment from p to infinite
	Position extreme = {overflow, p.y};

	// To count number of points in polygon whose y-coordinate is equal to
	// y-coordinate of the point
	int decrease = 0;

	// Count intersections of the above line with sides of polygon
	int count = 0;
    int i = 0;

	do
	{
		int next = (i+1)%n;
	
		if(polygon[i].y == p.y) decrease++;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment.
            // If it lies, return true, otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
			    return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);
	
    // Reduce the count by decrease amount
    // as these points would have been added twice
	count -= decrease;

	// Return true if count is odd, false otherwise
	return count&1; // Same as (count%2 == 1)
}

void generatePixelsCenters(std::vector<Position>& pixels_centers)
{
    // Create center points of the first pixel
    double relPixCent{ pixel_size / 2.0 };
	double absPixCent_x;
	double absPixCent_y;

    for (int y = height; y > 0; y--)
    {
		absPixCent_y = y - relPixCent;
        for (int x = 0; x < width; x++)
        {
			absPixCent_x = x + relPixCent;
			pixels_centers.push_back({absPixCent_x, absPixCent_y});
        }
    }
}

// Driver program to test above functions
int main()
{
    // Create .ppm image
    std::ofstream img("image_small.ppm");

	// Insert .ppm tag at the beginning of the image
    img << "P3" << std::endl;
    img << width << " " << height << std::endl;
    img << "255" << std::endl;

	// Generate and save center position of every pixel
    std::vector<Position> pixels_centers;
    generatePixelsCenters(pixels_centers);

	Position region1[] = { {1.0, 0.0}, {2.0, 2.0}, {3.0, 0.0} };
    Position region2[] = { {2.0, 2.0}, {2.0, 4.0}, {4.0, 4.0}, {4.0, 2.0} };

	int n1 = sizeof(region1)/sizeof(region1[0]);
	int n2 = sizeof(region2)/sizeof(region2[0]);

    int count{ 1 };
	for (auto point : pixels_centers)
    {
        //std::cout << "Point: (" << point.x << ", " << point.y << ") \n";
        if (isInside(region1, n1, point)
		   || isInside(region2, n2, point))
        {
            std::cout << "W";
            img << 255 << " " << 255 << " " << 255 << std::endl;
        }
        else
        {
            std::cout << "B";
            img << 0 << " " << 0 << " " << 0 << std::endl;
        }
        if (count >= width)
        {
            std::cout << '\n';
            count = 1;
            continue;
        }
        count++;
    }

    system("explorer image_small.ppm");

	return 0;
}
