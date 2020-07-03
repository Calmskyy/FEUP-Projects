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
			-0.5, -0.5, -0.5,	//0
			-0.5, -0.5, 0.5,	//1
			-0.5, 0.5, -0.5,	//2
			-0.5, 0.5, 0.5,		//3
			0.5, -0.5, -0.5,    //4
			0.5, -0.5, 0.5,		//5
			0.5, 0.5, -0.5,		//6
			0.5, 0.5, 0.5		//7
		];

		//Counter-clockwise reference of vertices
		this.indices = [
			7, 3, 1,
			1, 5, 7,
			5, 4, 7,
			4, 6, 7,
			4, 5, 1, //
			0, 4, 1, //
			7, 6, 3,
			3, 6, 2,
			0, 1, 3, //
			2, 0, 3, //
			4, 0, 2, //
			6, 4, 2, //
		];
		this.primitiveType = this.scene.gl.TRIANGLES;
		this.initGLBuffers();
	}
}

