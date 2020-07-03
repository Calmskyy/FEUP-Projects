/**
 * MyUnitCube
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyUnitCube extends CGFobject {
	constructor(scene) {
		super(scene);
		this.initBuffers();
	}
	initBuffers() {
		this.vertices = [
			-0.5, -0.5, -0.5,	//0 0
			-0.5, -0.5, -0.5,	//0 1
			-0.5, -0.5, -0.5,	//0 2
			-0.5, -0.5, 0.5,	//1 3
			-0.5, -0.5, 0.5,	//1 4
			-0.5, -0.5, 0.5,	//1 5
			-0.5, 0.5, -0.5,	//2 6
			-0.5, 0.5, -0.5,	//2 7 
			-0.5, 0.5, -0.5,	//2 8
			-0.5, 0.5, 0.5,		//3 9
			-0.5, 0.5, 0.5,		//3 10
			-0.5, 0.5, 0.5,		//3 11
			0.5, -0.5, -0.5,    //4 12
			0.5, -0.5, -0.5,    //4 13
			0.5, -0.5, -0.5,    //4 14
			0.5, -0.5, 0.5,		//5 15
			0.5, -0.5, 0.5,		//5 16
			0.5, -0.5, 0.5,		//5 17
			0.5, 0.5, -0.5,		//6 18
			0.5, 0.5, -0.5,		//6 19
			0.5, 0.5, -0.5,		//6 20 
			0.5, 0.5, 0.5,		//7 21
			0.5, 0.5, 0.5,		//7 22
			0.5, 0.5, 0.5		//7 23
		];

		//Counter-clockwise reference of vertices
		this.indices = [
			5, 11, 23, //
			23, 17, 5, //
			21, 12, 15, // 
			21, 18, 12, //
			4, 16, 13, //
			4, 13, 1, //
			10, 19, 22, //
			7, 19, 10, //
			9, 3, 0, //
			9, 0, 6, //
			8, 2, 14, 
			8, 14, 20
		];

		this.normals = [
			1, 0, 0,	//0  0
			0, 1, 0,	//0  1
			0, 0, 1,   //0  2
			1, 0, 0,	//1  3
			0, 1, 0,	//1  4
			0, 0, -1,	//1  5
			1, 0, 0,	//2  6
			0, -1, 0,	//2  7
			0, 0, 1,	//2  8
			1, 0, 0,	//3  9
			0, -1, 0,	//3  10
			0, 0, -1,	//3  11
			-1, 0, 0,    //4  12
			0, 1, 0,   //4  13
			0, 0, 1,   //4  14 
			-1, 0, 0,	//5  15
			0, 1, 0,	//5  16
			0, 0, -1,	//5  17
			-1, 0, 0,	//6  18
			0, -1, 0,	//6  19
			0, 0, 1,	//6  20
			-1, 0, 0,	//7  21
			0, -1, 0,	//7  22
			0, 0, -1,	//7  23
		];

		this.primitiveType = this.scene.gl.TRIANGLES;
		this.initGLBuffers();
	}
}

