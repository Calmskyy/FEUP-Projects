/**
 * MyTorch
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyTorch extends CGFobject {
	constructor(scene, light) {
		super(scene);
		this.initBuffers();
		this.light = light;
		
        this.fireTexture = new CGFappearance(this.scene);
        this.fireTexture.setAmbient(1, 1, 1, 1);
        this.fireTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.fireTexture.setSpecular(0.0, 0.0, 0.0, 1);
        this.fireTexture.setShininess(10.0);
		this.fireTexture.loadTexture('textures/fire.jpg');
		
		this.structureTexture = new CGFappearance(this.scene);
		this.structureTexture.setAmbient(0, 0, 0, 1);
		this.structureTexture.setDiffuse(0.9, 0.9, 0.9, 1);
		this.structureTexture.setSpecular(0.1, 0.1, 0.1, 1);
		this.structureTexture.setShininess(10.0);
		this.structureTexture.loadTexture('textures/torch.jpg');

		this.fire = new MyUnitCubeQuad(this.scene);
		this.structure = new MyUnitCubeQuad(this.scene);
	}

	initBuffers() {
		this.vertices = [
		];

		this.indices = [
		];

		this.primitiveType = this.scene.gl.TRIANGLES;
		this.initGLBuffers();
	}

	display() {
		this.scene.pushMatrix();

		this.scene.scale(1, 4, 1);
		this.scene.translate(0, 0.505, 0);
		this.structureTexture.apply();
		this.structure.display();

		this.scene.popMatrix();

		if (this.light == 1) {
			this.scene.pushMatrix();

			this.scene.scale(1.2, 1.2, 1.2);
			this.scene.translate(0, 3.8, 0);
			this.fireTexture.apply();
			this.fire.display();

			this.scene.popMatrix();
		}
	}
	updateTorch(light) {
		this.light = light;
	}
}

