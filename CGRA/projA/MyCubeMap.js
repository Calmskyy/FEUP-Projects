/**
 * MyCubeMap
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyCubeMap extends CGFobject {
	constructor(scene) {
		super(scene);
		this.scene = scene;
		this.skybox = new MyUnitCube(scene);
		
		this.initBuffers();
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

		this.scene.translate(0, 0, 0);
		this.scene.scale(200, 200, 200);
		this.skybox.display();

        this.scene.popMatrix();
    }
}

