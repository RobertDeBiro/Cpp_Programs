	// Count intersections of the above line with sides of region
	int count = 0;
    int i = 0;
	int next = 1;

	do
	{
		//int next = (i+1)%n;
	
		if(region[i].y == p.y) decrease++;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'region[i]' to 'region[next]'
		if (linesIntersect(region[i], region[next], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment.
            // If it lies, return true, otherwise false
			if (orientation(region[i], region[next], p) == 0)
			    return posOnLine(region[i], region[next], p);

			count++;
		}

		++next;
		if (++i == n)
			next = 1;

	} while (i <= n);