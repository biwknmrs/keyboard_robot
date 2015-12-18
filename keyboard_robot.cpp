

#include "keyboard_robot.h"

float pos_x = 0.0; // ロボット位置
float pos_z = 0.0; // ロボット位置
float speed = 0.3;

bool up		= false;
bool down	= false;
bool left	= false;
bool right	= false;

bool click = false;

float dir = 0.0;// ロボットの向き
float rot = 15.0; // 回転角

float Body = 0.0;// 胴体の回転角度
float R_leg = 0.0; // 右足の回転角度
float L_leg = 0.0; // 左足の回転角度
float R_arm = 0.0; // 右腕の回転角度
float L_arm = 0.0; // 左腕の回転角度

float e = 2.0;

int mouseX, mouseY;

//--初期化処理------------------------------------------------------------------
void myinit(void)
{
	glfwInit();
	glfwOpenWindow( 600, 600, 0, 0, 0, 0, 16,0, GLFW_WINDOW);

	glfwSetWindowTitle("keyboard_robot");	/* ウィンドウのタイトル */
	glfwSetWindowPos(700,200);				/* ウィンドウが表示される位置 */

	glClearColor(0.9, 0.9, 0.9, 0.5);		/* 背景色の設定(R,G,B,ALPHA) 0.0-1.0の範囲で */

	glEnable( GL_DEPTH_TEST );				/* デプスバッファの有効化 */

	//glfwEnable(GLFW_KEY_REPEAT); 			/* 必要に応じて有効にしてください */

	printf("\n");
	printf("スペースで初期化\n");
	printf("小人が枠の中に入っている時にマウスクリックすると捕まえられます。\n");
	printf("捕まえてドラッグすると小人が暴れます。\n");

}

//--再描画----------------------------------------------------------------------
void GLFWCALL reshape( int w, int h )
{
	/* 描画モードの設定 */
	glViewport( 0, 0, (GLsizei)w, (GLsizei)h );	/* ウィンドウ全体をビューポートにする  */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();			/* 変換行列の初期化  */

	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

	/* カメラ位置と,どこを見ているかを設定する */
	gluLookAt(					
		0.0, 15.0, 15.0,		/* カメラの位置(x,y,z) */
		0.0, 0.0, 0.0,			/* 注視点の位置(x,y,z) */
		0.0, 1.0, 0.0			/* y座標が上を向いているということを示す */
	);
}

//--描画内容--------------------------------------------------------------------
void display(int frame)
{
	/* バッファクリア */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	
	

	// 何らかのキーが押されているとき
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
		// ↑
		if( frame >= 0 && frame < 50){
			pos_z -= speed;
			dir = 180.0;
		}
	
		// ↓
		if( frame >= 50 && frame < 100){
			pos_z += speed;
			dir = 0.0;
		}
	
		// ←
		if(  frame >= 100 && frame < 150 ){
			pos_x -= speed;
			dir = 270.0;
		}
	
		// →
		if(  frame >= 150 && frame < 200 ){
			pos_x += speed;
			dir = 90.0;
		}
	
		// ↓
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
		glRotated( dir, 0.0, 1.0, 0.0 );//腰(全体)の回転*****
		glRotated(Body* 0.6, 0.0, 1.0, 0.0 );//胴体の回転*****
		makebox(0.4,0.4,0.4, GL_POLYGON); //胴

		glPushMatrix();
			glTranslatef(0, 0.5, 0);
			makebox(0.4,0.4,0.4, GL_POLYGON); //頭

			glPushMatrix();
				glTranslatef(0.1, 0.1, 0.25);
				makeboxB(0.03,0.03,0.03, GL_POLYGON); //目
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.1, 0.1, 0.25);
				makeboxB(0.03,0.03,0.03, GL_POLYGON); //目
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.0, -0.1, 0.25);
				makeboxB(0.03,0.03,0.03, GL_POLYGON); //口
			glPopMatrix();

		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.1, 0.0, 0.0);
			glRotated(L_leg*1.0,1,0,0);
			glTranslatef(0, -0.5, 0);
			makebox(0.1,0.4,0.2, GL_POLYGON); //左足
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.1, 0.0, 0.0);
			glRotated(R_leg*1.0,1,0,0);
			glTranslatef(0, -0.5, 0);
			makebox(0.1,0.4,0.2, GL_POLYGON); //右足
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -0.1, 0.0);
			glRotatef(-45, 0,0,1);
			glRotated(L_arm,1,0,0);
			glTranslatef(0.2, 0.3, 0.0);
			makebox(0.4,0.1,0.2, GL_POLYGON); //左腕
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0, -0.1, 0.0);
			glRotatef(45, 0,0,1);
			glRotated(R_leg,1,0,0);
			glTranslatef(-0.2, 0.3, 0.0);
			makebox(0.4,0.1,0.2, GL_POLYGON); //右腕
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

//--キーボード関数１（矢印キーやスペースキーなど）------------------------------
void GLFWCALL KeyFunc(int key,int action)
{ 
	//今回はswitch文で制御します
	switch( key ){
		case GLFW_KEY_UP:	//↑
			if( action == GLFW_PRESS ){ //ボタン押した
				up = true;
			}
			if( action == GLFW_RELEASE ){ //ボタン離した
				up = false;
			}
			break;

		case GLFW_KEY_DOWN:	//↓
			if( action == GLFW_PRESS ){ //ボタン押した
				down  = true;
			}
			if( action == GLFW_RELEASE ){ //ボタン離した
				down = false;
			}
			break;

		case GLFW_KEY_LEFT:	//←
			if( action == GLFW_PRESS ){ //ボタン押した
				left  = true;
			}
			if( action == GLFW_RELEASE ){ //ボタン離した
				left = false;
			}
			break;

		case GLFW_KEY_RIGHT://→
			if( action == GLFW_PRESS ){ //ボタン押した
				right  = true;
			}
			if( action == GLFW_RELEASE ){ //ボタン離した
				right = false;
			}
			break;

		case GLFW_KEY_SPACE:
			if( action == GLFW_PRESS ){ //ボタン押した
				pos_x = 0.0;
				pos_z = 0.0;
				dir = 0.0;
				Body = 0.0;
				R_leg = 0.0; // 右足の回転角度
				L_leg = 0.0; // 左足の回転角度
				R_arm = 0.0; // 右腕の回転角度
				L_arm = 0.0; // 左腕の回転角度
			}
			if( action == GLFW_RELEASE ){ //ボタン離した
				//pos_z += 0.5;
			}

		default:
			break;
	}
} 

//--マウスボタン関数------------------------------------------------------------
void GLFWCALL MouseButtonFunc(int button, int action){


	/* 
     * わざと、「押した」「離した」の区別を付けないようにしています
	 * 必要であれば↑↓←→キーの例を参考に「押した」「離した」を区別するように書き直してみてください
     */
	
	bool flag_x = ( -e < pos_x ) && (pos_x < e);
	bool flag_z = ( -e < pos_z ) && (pos_z < e);

	if(flag_x && flag_z ){
		switch( button ){
			case GLFW_MOUSE_BUTTON_LEFT:
				if( action == GLFW_PRESS ){ //ボタン押した
					click = true;
				}if( action == GLFW_RELEASE ){ //ボタン離した
					click = false;
				}
				break;
			default:
				break;
		}
	}
			
	/*
		case GLFW_MOUSE_BUTTON_RIGHT:
			printf("マウスの右ボタン\n");
			break;
			
		case GLFW_MOUSE_BUTTON_MIDDLE:
			printf("マウスの中ボタン\n");
			break;
	*/
	
} 

//--マウスの位置関数------------------------------------------------------------
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

//--マウスのホイール関数--------------------------------------------------------
void GLFWCALL MouseWheelFunc(int pos){

	//printf("wheel pos : (%d)\n",pos);
	
}  

//--メイン関数------------------------------------------------------------------
int main(void){
	
	int running;
	int frame=0;

	//初期化処理 (ウィンドウサイズや表示位置、タイトル、背景色、...を決める)
	//----------------------------------------------------------------
	myinit();
	
	//コールバック関数 (キーボードやマウスの動きを捕まえる)
	//----------------------------------------------------------------
	glfwSetWindowSizeCallback( reshape );				/* ウィンドウのサイズを変えると呼び出される */
	glfwSetKeyCallback( KeyFunc );						/* キーボードを触ると呼び出される */
	glfwSetMouseButtonCallback( MouseButtonFunc );		/* マウスのボタンを押すと呼び出される */
	glfwSetMousePosCallback( MousePosFunc );			/* マウスを動かすと呼び出される */
	glfwSetMouseWheelCallback( MouseWheelFunc );		/* マウスホイールを動かすと呼び出される */

	//イベント処理ループ
	//--------------------------------------------------------
	do{
		frame++;
		if(MAXFRAME<frame){
			frame=0;
		}
		display(frame);
		glfwSwapBuffers();

		/* ウィンドウが表示されているときにESCキーが押されたら終了する */
		running = !( glfwGetKey( GLFW_KEY_ESC ) &&
					 glfwGetWindowParam( GLFW_OPENED ));
	}while( running );

	glfwTerminate();

	return 0;
}
void makeboxB(double width, double height, double length, GLenum type)
{
	double box[8][3];	//頂点データ格納用配列

	//頂点データの格納
	box[0][0] = -width/2;	box[0][1] =  height/2;	box[0][2] = length/2;	
	box[1][0] = -width/2;	box[1][1] = -height/2;	box[1][2] = length/2;
	box[2][0] =  width/2;	box[2][1] = -height/2;	box[2][2] = length/2;
	box[3][0] =  width/2;	box[3][1] =  height/2;	box[3][2] = length/2;
	
	box[4][0] = -width/2;	box[4][1] =  height/2;	box[4][2] = -length/2;
	box[5][0] = -width/2;	box[5][1] = -height/2;	box[5][2] = -length/2;
	box[6][0] =  width/2;	box[6][1] = -height/2;	box[6][2] = -length/2;
	box[7][0] =  width/2;	box[7][1] =  height/2;	box[7][2] = -length/2;

	//前面描画
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[0]);
		glVertex3dv(box[1]);
		glVertex3dv(box[2]);
		glVertex3dv(box[3]);
	glEnd();

	//後面描画
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[4]);
		glVertex3dv(box[5]);
		glVertex3dv(box[6]);
		glVertex3dv(box[7]);
	glEnd();
	
	//上面描画
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[4]);
		glVertex3dv(box[0]);
		glVertex3dv(box[3]);
		glVertex3dv(box[7]);
	glEnd();

	//右面描画
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[3]);
		glVertex3dv(box[2]);
		glVertex3dv(box[6]);
		glVertex3dv(box[7]);
	glEnd();

	//左面描画
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[4]);
		glVertex3dv(box[5]);
		glVertex3dv(box[1]);
		glVertex3dv(box[0]);
	glEnd();
	
	//下面描画
	glColor3d(0,0,0);
	glBegin(type);
		glVertex3dv(box[6]);
		glVertex3dv(box[5]);
		glVertex3dv(box[1]);
		glVertex3dv(box[2]);
	glEnd();
}