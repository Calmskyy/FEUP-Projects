/**
 * MyTangram
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyTangram extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initBuffers();
        this.diamond = new MyDiamond(scene);
        this.triangle = new MyTriangle(scene);
        this.paralellogram = new MyParalellogram(scene);
        this.triangleSmall = new MyTriangleSmall(scene);
        this.triangleBig = new MyTriangleBig(scene);
        this.triangleBig2 = new MyTriangleBig(scene);
        this.triangleSmall2 = new MyTriangleSmall(scene);
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
    display(scene) {

        scene.translate(1, 3, 0);
        scene.materials[3].apply();
        this.diamond.display();

        scene.translate(-0.5, -2.5, 0);
        scene.materials[5].apply();
        this.triangleBig.display();

        scene.rotate(Math.PI / 4, 0, 0, 1);
        scene.translate(-1.4, -0.6, 0);
        scene.materials[6].apply();
        this.triangleBig2.display();

        scene.rotate(Math.PI / 4, 0, 0, -1)
        scene.translate(-0.4, -1.4, 0);
        scene.materials[7].apply();
        this.triangleSmall.display();

        scene.rotate(Math.PI / 2, 0, 0, 1);
        scene.translate(1, -1, 0);
        scene.materials[8].apply();
        this.triangleSmall2.display();

        scene.rotate(Math.PI / 2, 0, 0, 1);
        scene.translate(1, 2, 0);
        scene.materials[9].apply();
        this.triangle.display();

        scene.rotate(Math.PI, 0, 1, 0);
        scene.translate(-2, 0, 0);
        scene.materials[10].apply();
        this.paralellogram.display();
    }
}

