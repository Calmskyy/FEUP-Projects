/**
 * MyWaterContainer
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyWaterContainer extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initBuffers();
        this.scene = scene;

        this.waterTexture = new CGFappearance(this.scene);
        this.waterTexture.setAmbient(0, 0, 0, 1);
        this.waterTexture.setDiffuse(0.1, 0.1, 0.1, 1);
        this.waterTexture.setSpecular(1.0, 1.0, 1.0, 1);
        this.waterTexture.setShininess(10.0);
        this.waterTexture.loadTexture('textures/water.png');

        this.stoneTexture = new CGFappearance(this.scene);
        this.stoneTexture.setAmbient(0, 0, 0, 1);
        this.stoneTexture.setDiffuse(1, 1, 1, 1);
        this.stoneTexture.setSpecular(0, 0, 0, 1);
        this.stoneTexture.setShininess(10.0);
        this.stoneTexture.loadTexture('textures/stone.jpg');

        this.container = new MyUnitCubeQuad(this.scene);
        this.water = new MyUnitCubeQuad(this.scene);
    }
    initBuffers() {
        this.vertices = [
        ];

        //Counter-clockwise reference of vertices
        this.indices = [
        ];
        this.primitiveType = this.scene.gl.TRIANGLES;
        this.initGLBuffers();
    }
    display() {
        this.scene.pushMatrix();

        this.scene.translate(0, 0.6, 0);
        this.scene.scale(20, 1, 20);
        this.waterTexture.apply();
        this.water.display();
        this.scene.translate(0, -0.1, 0);

        this.scene.scale(1.2, 1, 1.2);
        this.stoneTexture.apply();
        this.container.display();

        this.scene.popMatrix();
    }
}