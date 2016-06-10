bool showGraph = false;
bool solved = false;

void drawMaze()
{
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
		{
		glBegin(GL_QUADS);
		if (mazeArray[i][j] == CLEAR)
			glColor3f(1.0, 1.0, 1.0);
		else
			glColor3f(0.3, 0.3, 0.3);
		glVertex2i(j, i);
		glVertex2i(j, i + 1);
		glVertex2i(j + 1, i + 1);
		glVertex2i(j + 1, i);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3f(0.6, 0.6, 0.6);
		glVertex2i(j, i);
		glVertex2i(j, i + 1);
		glVertex2i(j + 1, i + 1);
		glVertex2i(j + 1, i);
		glEnd();
		}
}

void drawPath()
{
	glLineWidth(3);
	glColor3f(0.0, 0.8, 0.0);
	int i = cellsCount - 1 - rows;

	while (mazeGraph.vertices[i].path != NULL)
	{
		int row = i / rows;
		int col = i % rows;
		glBegin(GL_LINES);
		glVertex2f(col + 0.5, row + 0.5);

		i = mazeGraph.vertices[i].path->id;
		row = i / rows;
		col = i % rows;

		glVertex2f(col + 0.5, row + 0.5);
		glEnd();
	}

	glBegin(GL_LINES);
	glVertex2f(0 - 0.5, 1 + 0.5);
	glVertex2f(0 + 0.5, 1 + 0.5);

	glVertex2f(columns - 1 + 0.5, rows - 2 + 0.5);
	glVertex2f(columns + 0.5, rows - 2 + 0.5);
	glEnd();

	glLineWidth(1);
	glFlush();
}

void drawGraph()
{
	glLineWidth(2);
	glPointSize(5);
	glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
			glVertex2f(j + 0.5, i + 0.5);
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i<rows; i++)
		for (int j = 0; j<columns; j++)
		{
		for (list<vertex*>::iterator itr = mazeGraph.vertices[i*columns + j].neighbors.begin();
			itr != mazeGraph.vertices[i*columns + j].neighbors.end(); itr++)
		{
			int nbr_id = (*itr)->id;
			int row = nbr_id / columns;
			int col = nbr_id % columns;
			glVertex2f(j + 0.5, i + 0.5);
			glVertex2f(col + 0.5, row + 0.5);
		}
		}
	glEnd();
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawMaze();
	if (showGraph) drawGraph();
	if (solved) drawPath();
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!showGraph)
		{
			showGraph = true;
			solved = false;
		}
		else
		{
			showGraph = false;
			solveMazeAndPrintPath();
			solved = true;
		}
		glutPostRedisplay();
	}
}

void startGraphicsLoop(int argc, char** argv)
{
	// These are the GLUT functions to set up the window and main loop
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Maze Solver");

	// set up viewing mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, columns + 1, rows + 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set up event handlers
	glutDisplayFunc(display);
	glutMouseFunc(mouse);

	glutMainLoop();
}