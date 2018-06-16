

#include "keyboard_robot.h"

float pos_x = 0.0; // ���{�b�g�ʒu
float pos_z = 0.0; // ���{�b�g�ʒu
float speed = 0.3;

bool up		= false;
bool down	= false;
bool left	= false;
bool right	= false;

bool click = false;

float dir = 0.0;// ���{�b�g�̌���
float rot = 15.0; // ��]�p

float Body = 0.0;// ���̂̉�]�p�x
float R_leg = 0.0; // �E���̉�]�p�x
float L_leg = 0.0; // �����̉�]�p�x
float R_arm = 0.0; // �E�r�̉�]�p�x
float L_arm = 0.0; // ���r�̉�]�p�x

float e = 2.0;

int mouseX, mouseY;

//--����������------------------------------------------------------------------
void myinit(void)
{
	glfwInit();
	glfwOpenWindow( 600, 600, 0, 0, 0, 0, 16,0, GLFW_WINDOW);

	glfwSetWindowTitle("keyboard_robot");	/* �E�B���h�E�̃^�C�g�� */
	glfwSetWindowPos(700,200);				/* �E�B���h�E���\�������ʒu */

	glClearColor(0.9, 0.9, 0.9, 0.5);		/* �w�i�F�̐ݒ�(R,G,B,ALPHA) 0.0-1.0�͈̔͂� */

	glEnable( GL_DEPTH_TEST );				/* �f�v�X�o�b�t�@�̗L���� */

	//glfwEnable(GLFW_KEY_REPEAT); 			/* �K�v�ɉ����ėL���ɂ��Ă������� */

	printf("\n");
	printf("�X�y�[�X�ŏ�����\n");
	printf("���l���g�̒��ɓ����Ă��鎞�Ƀ}�E�X�N���b�N����ƕ߂܂����܂��B\n");
	printf("�߂܂��ăh���b�O����Ə��l���\��܂��B\n");

}

//--�ĕ`��----------------------------------------------------------------------
void GLFWCALL reshape( int w, int h )
{
	/* �`�惂�[�h�̐ݒ� */
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );	/* �E�B���h�E�S�̂��r���[�|�[�g�ɂ���  */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();			/* �ϊ��s��̏�����  */

	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

	/* �J�����ʒu��,�ǂ������Ă��邩��ݒ肷�� */
	gluLookAt(					
		0.0, 15.0, 15.0,		/* �J�����̈ʒu(x,y,z) */
		0.0, 0.0, 0.0,			/* �����_�̈ʒu(x,y,z) */
		0.0, 1.0, 0.0			/* y���W����������Ă���Ƃ������Ƃ����� */
	);
}

//--�`����e--------------------------------------------------------------------
void display(int frame)
{
	/* �o�b�t�@�N���A */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	

	// ���炩�̃L�[��������Ă���Ƃ�
	if(true){
	    Body += rot;
	    R_leg += rot;
	    L_leg  = -R_leg;

	    R_arm  = L_leg;
	    L_arm  = R_leg;

	    if( 45.0 <= R_leg || R_leg <= -45.0){
	        rot = -rot;
	    }
	}
	if(click == false ){
		// ��
		if( frame >= 0 && frame < 50){
			pos_z -= speed;
			dir = 180.0;
		}
	
		// ��
		if( frame >= 50 && frame < 100){
			pos_z += speed;
			dir = 0.0;
		}
	
		// ��
		if(  frame >= 100 && frame < 150 ){
			pos_x -= speed;
			dir = 270.0;
		}
	
		// ��
		if(  frame >= 150 && frame < 200 ){
			pos_x += speed;
			dir = 90.0;
		}
	
		// ��
		if(  frame >= 200 && frame < 250 ){
			pos_x += speed;
			dir = 90.0;
		}
		if( frame >= 250 && frame < 300){
			pos_x -= speed;
			dir = 270.0;
		}
	}
	
	glPushMatrix();
		glTranslated( pos_x, 0.0, pos_z );
		glRotated( dir, 0.0, 1.0, 0.0 );//��(�S��)�̉�]*****
		glRotated(Body* 0.6, 0.0, 1.0, 0.0 );//���̂̉�]*****
		makebox(0.4,0.4,0.4, GL_POLYGON); //��

		glPushMatrix();
			glTranslatef(0, 0.5, 0);
			makebox(0.4,0.4,0.4, GL_POLYGON); //��

			glPushMatrix();
				glTranslatef(0.1, 0.1, 0.25);
				makeboxB(0.03,0.03,0.03, GL_POLYGON); //��
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.1, 0.1, 0.25);
				makeboxB(0.03,0.03,0.03, GL_POLYGON); //��
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -0.1, 0.25);
				makeboxB(0.03,0.03,0.03, GL_POLYGON); //��
			glPopMatrix();

		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.1, 0.0, 0.0);
			glRotated(L_leg*1.0,1,0,0);
			glTranslatef(0, -0.5, 0);
			makebox(0.1,0.4,0.2, GL_POLYGON); //����
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.1, 0.0, 0.0);
			glRotated(R_leg*1.0,1,0,0);
			glTranslatef(0, -0.5, 0);
			makebox(0.1,0.4,0.2, GL_POLYGON); //�E��
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -0.1, 0.0);
			glRotatef(-45, 0,0,1);
			glRotated(L_arm,1,0,0);
			glTranslatef(0.2, 0.3, 0.0);
			makebox(0.4,0.1,0.2, GL_POLYGON); //���r
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -0.1, 0.0);
			glRotatef(45, 0,0,1);
			glRotated(R_leg,1,0,0);
			glTranslatef(-0.2, 0.3, 0.0);
			makebox(0.4,0.1,0.2, GL_POLYGON); //�E�r
		glPopMatrix();

	glPopMatrix();

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
			glVertex3f(-e, -1.0, e);
			glVertex3f( e, -1.0, e);
			glVertex3f( e, -1.0, -e);
			glVertex3f(-e, -1.0, -e);
		glEnd();

}

//--�L�[�{�[�h�֐��P�i���L�[��X�y�[�X�L�[�Ȃǁj------------------------------
void GLFWCALL KeyFunc(int key,int action)
{ 
	//�����switch���Ő��䂵�܂�
	switch( key ){
		case GLFW_KEY_UP:	//��
			if( action == GLFW_PRESS ){ //�{�^��������
				up = true;
			}
			if( action == GLFW_RELEASE ){ //�{�^��������
				up = false;
			}
			break;

		case GLFW_KEY_DOWN:	//��
			if( action == GLFW_PRESS ){ //�{�^��������
				down  = true;
			}
			if( action == GLFW_RELEASE ){ //�{�^��������
				down = false;
			}
			break;

		case GLFW_KEY_LEFT:	//��
			if( action == GLFW_PRESS ){ //�{�^��������
				left  = true;
			}
			if( action == GLFW_RELEASE ){ //�{�^��������
				left = false;
			}
			break;

		case GLFW_KEY_RIGHT://��
			if( action == GLFW_PRESS ){ //�{�^��������
				right  = true;
			}
			if( action == GLFW_RELEASE ){ //�{�^��������
				right = false;
			}
			break;

		case GLFW_KEY_SPACE:
			if( action == GLFW_PRESS ){ //�{�^��������
				pos_x = 0.0;
				pos_z = 0.0;
				dir = 0.0;
				Body = 0.0;
				R_leg = 0.0; // �E���̉�]�p�x
				L_leg = 0.0; // �����̉�]�p�x
				R_arm = 0.0; // �E�r�̉�]�p�x
				L_arm = 0.0; // ���r�̉�]�p�x
			}
			if( action == GLFW_RELEASE ){ //�{�^��������
				//pos_z += 0.5;
			}

		default:
			break;
	}
} 

//--�}�E�X�{�^���֐�------------------------------------------------------------
void GLFWCALL MouseButtonFunc(int button, int action){


	/* 
     * �킴�ƁA�u�������v�u�������v�̋�ʂ�t���Ȃ��悤�ɂ��Ă��܂�
	 * �K�v�ł���΁��������L�[�̗���Q�l�Ɂu�������v�u�������v����ʂ���悤�ɏ��������Ă݂Ă�������
     */
	
	bool flag_x = ( -e < pos_x ) && (pos_x < e);
	bool flag_z = ( -e < pos_z ) && (pos_z < e);

	if(flag_x && flag_z ){
		switch( button ){
			case GLFW_MOUSE_BUTTON_LEFT:
				if( action == GLFW_PRESS ){ //�{�^��������
					click = true;
				}if( action == GLFW_RELEASE ){ //�{�^��������
					click = false;
				}
				break;
			default:
				break;
		}
	}
			
	/*
		case GLFW_MOUSE_BUTTON_RIGHT:
			printf("�}�E�X�̉E�{�^��\n");
			break;
			
		case GLFW_MOUSE_BUTTON_MIDDLE:
			printf("�}�E�X�̒��{�^��\n");
			break;
	*/
	
} 

//--�}�E�X�̈ʒu�֐�------------------------------------------------------------
void GLFWCALL MousePosFunc(int x, int y){
	
	mouseX = x;
	mouseY = y;

	

	if(click){
		pos_x =  ((float)mouseX - 300) / 300.0;
		pos_z =  ((float)mouseY - 300) / 300.0;
	}


	//printf("(x,y) = (%d, %d)\n",x,y);
	//printf("(x,y) = (%d, %d)\n",pos_x,pos_z);
	

} 

//--�}�E�X�̃z�C�[���֐�--------------------------------------------------------
void GLFWCALL MouseWheelFunc(int pos){

	//printf("wheel pos : (%d)\n",pos);
	
}  

//--���C���֐�------------------------------------------------------------------
int main(void){
	
	int running;
	int frame=0;

	//���������� (�E�B���h�E�T�C�Y��\���ʒu�A�^�C�g���A�w�i�F�A...�����߂�)
	//----------------------------------------------------------------
	myinit();
	
	//�R�[���o�b�N�֐� (�L�[�{�[�h��}�E�X�̓�����߂܂���)
	//----------------------------------------------------------------
	glfwSetWindowSizeCallback( reshape );				/* �E�B���h�E�̃T�C�Y��ς���ƌĂяo����� */
	glfwSetKeyCallback( KeyFunc );						/* �L�[�{�[�h��G��ƌĂяo����� */
	glfwSetMouseButtonCallback( MouseButtonFunc );		/* �}�E�X�̃{�^���������ƌĂяo����� */
	glfwSetMousePosCallback( MousePosFunc );			/* �}�E�X�𓮂����ƌĂяo����� */
	glfwSetMouseWheelCallback( MouseWheelFunc );		/* �}�E�X�z�C�[���𓮂����ƌĂяo����� */

	//�C�x���g�������[�v
	//--------------------------------------------------------
	do{
		frame++;
		if(MAXFRAME<frame){
			frame=0;
		}
		display(frame);
		glfwSwapBuffers();

		/* �E�B���h�E���\������Ă���Ƃ���ESC�L�[�������ꂽ��I������ */
		running = !( glfwGetKey( GLFW_KEY_ESC ) &&
					 glfwGetWindowParam( GLFW_OPENED ));
	}while( running );

	glfwTerminate();

	return 0;
}
void makeboxB(double width, double height, double length, GLenum type)
{
	double box[8][3];	//���_�f�[�^�i�[�p�z��

	//���_�f�[�^�̊i�[
	box[0][0] = -width/2;	box[0][1] =  height/2;	box[0][2] = length/2;	
	box[1][0] = -width/2;	box[1][1] = -height/2;	box[1][2] = length/2;
	box[2][0] =  width/2;	box[2][1] = -height/2;	box[2][2] = length/2;
	box[3][0] =  width/2;	box[3][1] =  height/2;	box[3][2] = length/2;
	
	box[4][0] = -width/2;	box[4][1] =  height/2;	box[4][2] = -length/2;
	box[5][0] = -width/2;	box[5][1] = -height/2;	box[5][2] = -length/2;
	box[6][0] =  width/2;	box[6][1] = -height/2;	box[6][2] = -length/2;
	box[7][0] =  width/2;	box[7][1] =  height/2;	box[7][2] = -length/2;

	//�O�ʕ`��
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[0]);
		glVertex3dv(box[1]);
		glVertex3dv(box[2]);
		glVertex3dv(box[3]);
	glEnd();

	//��ʕ`��
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[4]);
		glVertex3dv(box[5]);
		glVertex3dv(box[6]);
		glVertex3dv(box[7]);
	glEnd();
	
	//��ʕ`��
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[4]);
		glVertex3dv(box[0]);
		glVertex3dv(box[3]);
		glVertex3dv(box[7]);
	glEnd();

	//�E�ʕ`��
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[3]);
		glVertex3dv(box[2]);
		glVertex3dv(box[6]);
		glVertex3dv(box[7]);
	glEnd();

	//���ʕ`��
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[4]);
		glVertex3dv(box[5]);
		glVertex3dv(box[1]);
		glVertex3dv(box[0]);
	glEnd();
	
	//���ʕ`��
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[6]);
		glVertex3dv(box[5]);
		glVertex3dv(box[1]);
		glVertex3dv(box[2]);
	glEnd();
}