/**
 * MyUnitCubeQuad
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyUnitCubeQuad extends CGFobject {
	constructor(scene) {
		super(scene);
		this.scene = scene;
		this.initBuffers();

		this.quad = new MyQuad(scene);

		this.mineBottom = new CGFappearance(this.scene);
		this.mineBottom.setAmbient(0.1, 0.1, 0.1, 1);
		this.mineBottom.setDiffuse(0.9, 0.9, 0.9, 1);
		this.mineBottom.setSpecular(0.1, 0.1, 0.1, 1);
		this.mineBottom.setShininess(10.0);
		this.mineBottom.loadTexture('images/mineBottom.png');
		this.mineBottom.setTextureWrap('REPEAT', 'REPEAT');

		this.mineTop = new CGFappearance(this.scene);
		this.mineTop.setAmbient(0.1, 0.1, 0.1, 1);
		this.mineTop.setDiffuse(0.9, 0.9, 0.9, 1);
		this.mineTop.setSpecular(0.1, 0.1, 0.1, 1);
		this.mineTop.setShininess(10.0);
		this.mineTop.loadTexture('images/mineTop.png');
		this.mineTop.setTextureWrap('REPEAT', 'REPEAT');

		this.mineSide = new CGFappearance(this.scene);
		this.mineSide.setAmbient(0.1, 0.1, 0.1, 1);
		this.mineSide.setDiffuse(0.9, 0.9, 0.9, 1);
		this.mineSide.setSpecular(0.1, 0.1, 0.1, 1);
		this.mineSide.setShininess(10.0);
		this.mineSide.loadTexture('images/mineSide.png');
		this.mineSide.setTextureWrap('REPEAT', 'REPEAT');

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

		this.mineSide.apply();
		if (this.scene.selectedFilter == 1)
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
		else if (this.scene.selectedFilter == 0)
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.LINEAR);

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

		this.mineBottom.apply();
		if (this.scene.selectedFilter == 1)
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST)
		else if (this.scene.selectedFilter == 0)
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.LINEAR);

		this.scene.rotate(Math.PI / 2, 1, 0, 0);
		this.scene.translate(0, -0.5, 0.5);
		this.quad.display();

		this.mineTop.apply();
		if (this.scene.selectedFilter == 1)
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.NEAREST);
		else if (this.scene.selectedFilter == 0)
			this.scene.gl.texParameteri(this.scene.gl.TEXTURE_2D, this.scene.gl.TEXTURE_MAG_FILTER, this.scene.gl.LINEAR);

		this.scene.translate(0, 0, -1);
		this.scene.rotate(Math.PI, 1, 1, 0);
		this.quad.display();

	}
}

