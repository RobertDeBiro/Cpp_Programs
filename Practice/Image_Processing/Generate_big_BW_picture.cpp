#include <iostream>
#include <vector>
#include <array>
#include <fstream>

const int image_width = 480;
const int image_height = 480;
const int pixel_size = 1;
const long pixel_amount = (image_width / pixel_size) * (image_height / pixel_size);

struct Position
{
	double x;
	double y;
};

void generatePixelsCenters(std::vector<Position>& pixels_centers)
{
    double relPixCent{ pixel_size / 2.0 };
	double absPixCent_x;
	double absPixCent_y;

    for (int y = image_height; y > 0; y--)
    {
		absPixCent_y = y - relPixCent;
        for (int x = 0; x < image_width; x++)
        {
			absPixCent_x = x + relPixCent;
			pixels_centers.push_back({absPixCent_x, absPixCent_y});
        }
    }
}

// Check if position lies on line segment
bool posOnLine(Position pn, Position qn, Position pqm)
{
	// For three collinear positions - pn, qn and pqm - function returns true
	// if point pqm lies on line segment pn---qn, otherwise returns false
	if (pqm.x <= std::max(pn.x, qn.x) && pqm.x >= std::min(pn.x, qn.x))
		return true;
	
	return false;
}

// Return orientation of three ordered points
int orientation(Position pn, Position qn, Position pqm)
{
	/* 
	 * In order to find orientation of three ordered points use following algorithm:
	 * val = (y2 - y1) * (x3 - x2) - (y3 - y2) * (x2 - x1),
	 *
	 * where:	pn = [x1, y1]
	 *	 		qn = [x2, y2]
	 *	 		pqm = [x3, y3] 
	 *
	 * Orientation can be:
	 *  1) Collinear: 			val = 0
	 *  2) Clockwise: 			val > 0
	 *  3) CounterClockwise:	val < 0
	 */

	double val = (qn.y - pn.y) * (pqm.x - qn.x) - (pqm.y - qn.y) * (qn.x - pn.x);

	if(val == 0.0)		return 0;
	else if (val > 0.0)	return 1;
	else				return 2;
}

// Check if lines intersect
bool linesIntersect(Position p1, Position q1, Position p2, Position q2)
{
	/*
	 * Two lines - (p1, q1) and (p2, q2) - intersect if one of the following
	 * two conditions are satisfied:
	 *  1) General case:
	 *     (p1, q1, p2) and (p1, q1, q2) have different orientations, and
	 *     (p2, q2, p1) and (p2, q2, q1) have different orientations
	 *  2) Special Case:
	 *     (p1, q1, p2), (p1, q1, q2), (p2, q2, p1) and (p2, q2, q1) are all collinear, and
	 *	   the x-projections (or the y-projections) of (p1, q1) and (p2, q2) intersect
	 */
	
	// In order to find lines intersection we need to obtain four orientations
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && posOnLine(p1, q1, p2)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && posOnLine(p1, q1, q2)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && posOnLine(p2, q2, p1)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && posOnLine(p2, q2, q1)) return true;

	return false;
}

// Returns true if the point p lies inside the region[] with n vertices
bool isInside(Position region[], int vertices, Position p)
{
	// There must be at least 3 vertices in region[]
	if (vertices < 3) return false;

	// Create Position outside the image
	Position extreme = {image_width + 1, p.y};

	// Count intersections of the above line with sides of region
	int count = 0;
    int pos1 = 0;
	int pos2 = 1;

	do
	{
		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'region[i]' to 'region[next]'
		if (linesIntersect(region[pos1], region[pos2], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment.
            // If it lies, return true, otherwise false
			if (orientation(region[pos1], region[pos2], p) == 0)
			    return posOnLine(region[pos1], region[pos2], p);

			count++;
		}

		++pos1;
		if (++pos2 == vertices)
			pos2 = 0;

	} while (pos1 < vertices);

	// Return true if count is odd, false otherwise
	return (count%2 == 1);
}

int main()
{
	// Create .ppm image
    std::ofstream img("image.ppm");

	// Insert .ppm tag at the beginning of the image
    img << "P3" << std::endl;
    img << image_width << " " << image_height << std::endl;
    img << "255" << std::endl;

	// Generate and save center position of every pixel
    std::vector<Position> pixels_centers;
    generatePixelsCenters(pixels_centers);

	// Define regions
    Position region1[] = { {24.0, 432.0}, {72.0, 432.0}, {96.0, 96.0},
                           {120.0, 144.0}, {144.0, 96.0}, {168.0, 432.0},
                           {216.0, 432.0}, {168.0, 48.0}, {72.0, 48.0} };

    Position region2[] = { {240.0, 432.0}, {288.0, 432.0},
                           {288.0, 48.0}, {240.0, 48.0} };

    Position region3[] = { {312.0, 432.0}, {360.0, 432.0}, {408.0, 144.0},
                           {408.0, 432.0}, {456.0, 432.0}, {456.0, 48.0},
                           {408.0, 48.0}, {360.0, 240.0}, {360.0, 48.0},
                           {312.0, 48.0} };

	int n1 = sizeof(region1)/sizeof(region1[0]);
	int n2 = sizeof(region2)/sizeof(region2[0]);
	int n3 = sizeof(region3)/sizeof(region3[0]);

	// Generate black and white pixels for the image
    int count{ 1 };
	for (auto point : pixels_centers)
    {
        //std::cout << "Point: (" << point.x << ", " << point.y << ") \n";
        if (isInside(region1, n1, point)
		   || isInside(region2, n2, point)
		   || isInside(region3, n3, point))
        {
            std::cout << "W";
            img << 255 << " " << 255 << " " << 255 << std::endl;
        }
        else
        {
            std::cout << "B";
            img << 0 << " " << 0 << " " << 0 << std::endl;
        }
        if (count >= image_width)
        {
            std::cout << '\n';
            count = 1;
            continue;
        }
        count++;
    }

    system("explorer image.ppm");

	return 0;
}
