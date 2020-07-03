/**
 * MyVoxelHill
 * @constructor
 * @param scene - Reference to MyScene object  
 */
class MyVoxelHill extends CGFobject {
    constructor(scene, level) {
        super(scene);
        this.initBuffers();
        this.scene = scene;
        this.level = level;

        this.mineTop = new CGFappearance(this.scene);
        this.mineTop.setAmbient(0.1, 0.1, 0.1, 1);
        this.mineTop.setDiffuse(0.9, 0.9, 0.9, 1);
        this.mineTop.setSpecular(0.1, 0.1, 0.1, 1);
        this.mineTop.setShininess(10.0);
        this.mineTop.loadTexture('textures/mineTop.png');
        this.mineTop.setTextureWrap('REPEAT', 'REPEAT');

        this.mineSide = new CGFappearance(this.scene);
        this.mineSide.setAmbient(0.1, 0.1, 0.1, 1);
        this.mineSide.setDiffuse(0.9, 0.9, 0.9, 1);
        this.mineSide.setSpecular(0.1, 0.1, 0.1, 1);
        this.mineSide.setShininess(10.0);
        this.mineSide.loadTexture('textures/mineSide.png');
        this.mineSide.setTextureWrap('REPEAT', 'REPEAT');

        this.cube = new MyUnitCubeQuad(scene, this.mineTop, this.mineSide);
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
        for (let i = this.level; i >= 1; i--) {
            this.scene.pushMatrix();

            this.scene.translate(0, this.level - (i - 0.5), (i - 1));

            for (let j = i - 1; j > 0; j--) {
                this.cube.display();
                this.scene.translate(1, 0, 0);
            }
            for (let j = (i - 1) * 2; j > 0; j--) {
                this.cube.display();
                this.scene.translate(0, 0, -1);
            }
            for (let j = (i - 1) * 2; j > 0; j--) {
                this.cube.display();
                this.scene.translate(-1, 0, 0);
            }
            for (let j = (i - 1) * 2; j > 0; j--) {
                this.cube.display();
                this.scene.translate(0, 0, 1);
            }
            for (let j = i - 2; j > 0; j--) {
                this.cube.display();
                this.scene.translate(1, 0, 0);
            }

            this.cube.display();
            this.scene.popMatrix();
        }
    }
}