/**
 * MyTangram
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyTangram extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();

        var triangleNumber = 1;

        this.diamond = new MyDiamond(scene);
        this.triangle = new MyTriangle(scene);
        this.paralellogram = new MyParalellogram(scene);
        this.triangleSmall = new MyTriangleSmall(scene, triangleNumber);
        this.triangleBig = new MyTriangleBig(scene, triangleNumber);

        triangleNumber = 2;

        this.triangleSmall2 = new MyTriangleSmall(scene, triangleNumber);
        this.triangleBig2 = new MyTriangleBig(scene, triangleNumber);

        this.tangramMaterial = new CGFappearance(this.scene);
        this.tangramMaterial.setAmbient(0.1, 0.1, 0.1, 1);
        this.tangramMaterial.setDiffuse(0.9, 0.9, 0.9, 1);
        this.tangramMaterial.setSpecular(0.1, 0.1, 0.1, 1);
        this.tangramMaterial.setShininess(10.0);
        this.tangramMaterial.loadTexture('images/tangram.png');
        this.tangramMaterial.setTextureWrap('REPEAT', 'REPEAT');

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

        this.scene.translate(1, 3, 0);
        this.tangramMaterial.apply();
        this.diamond.display();

        this.scene.translate(-0.5, -2.5, 0);
        this.triangleBig.display();

        this.scene.rotate(Math.PI / 4, 0, 0, 1);
        this.scene.translate(-1.4, -0.6, 0);
        this.triangleBig2.display();

        this.scene.rotate(Math.PI / 4, 0, 0, -1)
        this.scene.translate(-0.4, -1.4, 0);
        this.triangleSmall.display();

        this.scene.rotate(Math.PI / 2, 0, 0, 1);
        this.scene.translate(1, -1, 0);
        this.triangleSmall2.display();

        this.scene.rotate(Math.PI / 2, 0, 0, 1);
        this.scene.translate(1, 2, 0);
        this.triangle.display();

        this.scene.rotate(Math.PI, 0, 1, 0);
        this.scene.translate(-2, 0, 0);
        this.paralellogram.display();
    }
}

