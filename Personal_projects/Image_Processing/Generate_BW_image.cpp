#include <iostream>
#include <fstream>
#include <vector>

// Image specifications
namespace image
{
	constexpr int width = 480;
	constexpr int height = 480;
	constexpr int pixel_size = 1;
}

struct Position
{
	double x{};
	double y{};
};

// Save the position of every pixel center
void generatePixelsCenters(std::vector<Position>& pixels_centers)
{
    double relPixCent{ image::pixel_size / 2.0 }; // relative position of the center for every pixel
	double absPixCent_x; // pixel center x coordinate
	double absPixCent_y; // pixel center y coordinate

    for (int y = image::height; y > 0; y--)
    {
		absPixCent_y = y - relPixCent;
        for (int x = 0; x < image::width; x++)
        {
			absPixCent_x = x + relPixCent;
			pixels_centers.push_back({absPixCent_x, absPixCent_y});
        }
    }
}

// Check if position collinear with the line lies on it
bool posOnLine(const Position pn, const Position qn, const Position pqm)
{
	// For three collinear positions - pn, qn and pqm - function returns true
	// if point pqm lies on line segment pn---qn, otherwise returns false
	if (pqm.x <= std::max(pn.x, qn.x) && pqm.x >= std::min(pn.x, qn.x))
		return true;
	
	return false;
}

// Return orientation of three ordered points
int orientation(const Position pn, const Position qn, const Position pqm)
{
	/* 
	 * In order to find orientation of three ordered points use following algorithm:
	 * orient = (y2 - y1) * (x3 - x2) - (y3 - y2) * (x2 - x1),
	 *
	 * where:	pn = [x1, y1]
	 *	 		qn = [x2, y2]
	 *	 		pqm = [x3, y3] 
	 *
	 * Orientation can be:
	 *  1) Collinear: 			orient = 0
	 *  2) Clockwise: 			orient > 0
	 *  3) CounterClockwise:	orient < 0
	 */

	double orient = (qn.y - pn.y) * (pqm.x - qn.x) - (pqm.y - qn.y) * (qn.x - pn.x);

	if(orient == 0.0)		return 0;
	else if (orient > 0.0)	return 1;
	else				return 2;
}

// Check if lines intersect
bool linesIntersect(const Position p1, const Position q1, const Position p2, const Position q2)
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

// Returns true if the pixel center 'p' lies inside the region
bool isPixelCenterInside(const std::vector<Position>& region, const Position p)
{
	// In order to check if pixel center p lies inside region, implement following logic:
	//  1) Create a horizontal line from the pixel center
    //     to the arbitrary position placed outside the image
	//  2) Count the number of times the created line intersects with region edges
	//  3) Pixel center is inside the region if one of the following is satisfied:
	//       a) count of intersections is odd
	//       b) point lies on an edge of the region
	
	// Arbitrary position outside the image
	Position extreme = {image::width + 1, p.y};

	// Amount of region vertices
	int vertices{ static_cast<int>(region.size()) };

	// Counter for counting intersections
	int count = 0;

	// Indexes for region adjacent vertices
    int pos1 = 0;
	int pos2 = 1;

	do
	{
		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'region[pos1]' to 'region[pos2]'
		if (linesIntersect(region[pos1], region[pos2], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'pos1-pos2', then
			// check if it lies on segment
			//  - if it lies on segment, pixel center
			//    is inside the region -> return true
			//  - if it doesn't lie on segment, then for sure pixel center
			//    is not inside the region -> return false
			if (orientation(region[pos1], region[pos2], p) == 0)
			    return posOnLine(region[pos1], region[pos2], p);

			count++;
		}

		++pos1;
		if (++pos2 == vertices) // last iteration pos2 must be equal to first vertice
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
    img << image::width << " " << image::height << std::endl;
    img << "255" << std::endl;

	// Generate and save center position of every pixel
    std::vector<Position> pixels_centers;
    generatePixelsCenters(pixels_centers);

	// Define regions
    std::vector<Position> region1 = {
										{24.0, 432.0}, {72.0, 432.0}, {96.0, 96.0},
                                        {120.0, 144.0}, {144.0, 96.0}, {168.0, 432.0},
                                        {216.0, 432.0}, {168.0, 48.0}, {72.0, 48.0}
									};

    std::vector<Position> region2 = {
										{240.0, 432.0}, {288.0, 432.0},
										{288.0, 48.0}, {240.0, 48.0}
									};

    std::vector<Position> region3 = {
										{312.0, 432.0}, {360.0, 432.0}, {408.0, 144.0},
                           				{408.0, 432.0}, {456.0, 432.0}, {456.0, 48.0},
                           				{408.0, 48.0}, {360.0, 240.0}, {360.0, 48.0},
                           				{312.0, 48.0}
									};

	// Generate black and white pixels for the image
	for (auto point : pixels_centers)
    {
        if (isPixelCenterInside(region1, point)
		   || isPixelCenterInside(region2, point)
		   || isPixelCenterInside(region3, point))
        {
			// If pixel center is inside the region, generate white pixel
            img << 255 << " " << 255 << " " << 255 << std::endl;
        }
        else
        {
			// If pixel center is outside the region, generate black pixel
            img << 0 << " " << 0 << " " << 0 << std::endl;
        }
    }

    system("explorer image.ppm");

	return 0;
}
