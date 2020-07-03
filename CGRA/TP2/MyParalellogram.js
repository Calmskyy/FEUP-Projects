/**
 * MyParalellogram
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyParalellogram extends CGFobject {
	constructor(scene) {
		super(scene);
		this.initBuffers();
	}
	initBuffers() {
		this.vertices = [
			0, 0, 0,	//0
			1, 1, 0,	//1
			2, 1, 0,	//2
			3, 1, 0,	//3
			2, 0, 0,	//4
			1, 0, 0,	//5
		];

		//Counter-clockwise reference of vertices
		this.indices = [
			0, 5, 1,
			5, 4, 1,
			1, 4, 2,
			2, 4, 3,
			1, 5, 0,
			1, 4, 5,
			2, 4, 1,
			3, 4, 2
		];

		this.primitiveType = this.scene.gl.TRIANGLES;
		this.initGLBuffers();
	}
}

