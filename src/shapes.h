//
// Created by mateu on 12/02/2024.
//

#ifndef ENGINE_PROJECT_SHAPES_H
#define ENGINE_PROJECT_SHAPES_H

/*
void drawBox(float c[3], float width, float height, float depth){
	float w = width;
	float h = height;
	float d = depth;

	float verticies[8][3] = {{c[0]-w,c[1]-h,c[2]+d},   {c[0]-w,c[1]+h,c[2]+d},   {c[0]+w,c[1]+h,c[2]+d},   {c[0]+w,c[1]-h,c[2]+d},
							{c[0]-w,c[1]-h,c[2]-d},    {c[0]-w,c[1]+h,c[2]-d},   {c[0]+w,c[1]+h,c[2]-d},   {c[0]+w,c[1]-h,c[2]-d}};

	glBegin(GL_POLYGON);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[6]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[3]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(verticies[3]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[0]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[1]);
	glVertex3fv(verticies[2]);
	glVertex3fv(verticies[6]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[7]);
	glVertex3fv(verticies[6]);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3fv(verticies[0]);
	glVertex3fv(verticies[4]);
	glVertex3fv(verticies[5]);
	glVertex3fv(verticies[1]);
	glEnd();


}
*/

void drawRoom(float c[3], float width, float height, float depth);

#endif //ENGINE_PROJECT_SHAPES_H
