/**
 * MyUnitCubeQuad
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyUnitCubeQuad extends CGFobject {
	constructor(scene, topTexture, sideTexture) {
		super(scene);
		this.scene = scene;
		this.topTexture = topTexture;
		this.sideTexture = sideTexture;
		this.initBuffers();
		this.quad = new MyQuad(scene);
	}
	initBuffers() {
		this.vertices = [
		];

		//Counter-clockwise reference of vertices
		this.indices = [
		];

		this.normals = [
		];

		this.primitiveType = this.scene.gl.TRIANGLES;
		this.initGLBuffers();
	}
	display() {
		this.scene.pushMatrix();

		if (this.sideTexture != null) {
			this.sideTexture.apply();
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
		}

		this.scene.translate(0, 0, 0.5);
		this.quad.display();

		this.scene.translate(0, 0, -1);
		this.scene.rotate(Math.PI, 1, 0, 0);
		this.scene.rotate(-Math.PI, 0, 0, 1);
		this.quad.display();

		this.scene.rotate(Math.PI / 2, 0, 1, 0);
		this.scene.translate(0.5, 0, 0.5);
		this.quad.display();

		this.scene.translate(0, 0, -1);
		this.scene.rotate(Math.PI, 0, 1, 0);
		this.quad.display();

		this.scene.rotate(Math.PI / 2, 1, 0, 0);
		this.scene.translate(0, -0.5, 0.5);
		this.quad.display();

		if (this.topTexture != null) {
			this.topTexture.apply();
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
		}

		this.scene.translate(0, 0, -1);
		this.scene.rotate(Math.PI, 1, 1, 0);
		this.quad.display();

		this.scene.popMatrix();
	}
}

