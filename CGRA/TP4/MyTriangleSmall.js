/**
 * MyTriangleSmall
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyTriangleSmall extends CGFobject {
	constructor(scene, triangleNumber) {
		super(scene);
		this.initBuffers(triangleNumber);
	}
	initBuffers(triangleNumber) {
		this.vertices = [
			1, 0, 0,	//0
			0, 1, 0,	//1
			-1, 0, 0	//2	
		];

		//Counter-clockwise reference of vertices
		this.indices = [
			0, 1, 2,
			2, 1, 0
		];

		this.normals = [
			0, 0, 1,
			0, 0, 1,
			0, 0, 1
		];

		if (triangleNumber == 1) {
			this.texCoords = [
				0.75, 0.75,
				0.5, 0.5,
				0.25, 0.75
			];
		}

		if (triangleNumber == 2) {
			this.texCoords = [
				0, 0,
				0.25, 0.25,
				0, 0.5
			];
		}

		this.primitiveType = this.scene.gl.TRIANGLES;
		this.initGLBuffers();
	}
}

