class MyWing extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;
        this.initBuffers();

        this.firstPart = new MyUnitCubeQuad(this.scene);
        this.secondPart = new MyUnitCubeQuad(this.scene);
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
    display(angle) {
        this.scene.pushMatrix();

        this.scene.scale(0.8, 0.1, 1);
        this.firstPart.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0.65, 0, 0);
        this.scene.translate(0, Math.sin(angle) / 2, 0);
        this.scene.rotate(angle, 0, 0, 1);
        this.scene.scale(1, 0.1, 1);

        this.secondPart.display();

        this.scene.popMatrix();
    }
}