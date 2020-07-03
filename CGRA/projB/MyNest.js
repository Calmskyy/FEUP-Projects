class MyNest extends CGFobject {
    constructor(scene) {
        super(scene);
        this.scene = scene;

        this.nestTexture = new CGFappearance(this.scene);
        this.nestTexture.setAmbient(0.509, 0.322, 0.004, 1);
        this.nestTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.nestTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.nestTexture.setShininess(10.0);
        this.nestTexture.loadTexture('textures/trunk.jpg');

        this.cube1 = new MyUnitCubeQuad(this.scene, this.nestTexture, this.nestTexture);
        this.cube2 = new MyUnitCubeQuad(this.scene, this.nestTexture, this.nestTexture);
        this.cube3 = new MyUnitCubeQuad(this.scene, this.nestTexture, this.nestTexture);
        this.cube4 = new MyUnitCubeQuad(this.scene, this.nestTexture, this.nestTexture);
        this.cube5 = new MyUnitCubeQuad(this.scene, this.nestTexture, this.nestTexture);
        this.branches = [null, null, null, null];
        this.numberOfBranches = 0;
    }
    initBuffers() {
        this.vertices = [
        ];

        //Counter-clockwise reference of vertices
        this.indices = [
        ];

        this.normals = [
        ];

        this.initGLBuffers();
    }
    display() {
        this.scene.pushMatrix();

        this.scene.translate(0, 0.1, 0);
        this.scene.scale(2, 0.2, 2);
        this.cube1.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        for (let i = 0; i < 4; i++) {
            if (this.branches[i] != null) {
                this.branches[i].display();
                if (i == 0)
                    this.scene.translate(0, 0, -0.5);
                else if (i == 1)
                    this.scene.translate(0, 0, -0.5);
                else if (i == 2) {
                    this.scene.translate(0, 0.8, 0.5);
                }
            }
        }

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 0.5, 1.1);
        this.scene.scale(2, 1, 0.2);
        this.cube2.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 0.5, -1.1);
        this.scene.scale(2, 1, 0.2);
        this.cube3.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.scene.translate(0, 0.5, 1.1);
        this.scene.scale(2.4, 1, 0.2);
        this.cube4.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.scene.translate(0, 0.5, -1.1);
        this.scene.scale(2.4, 1, 0.2);
        this.cube4.display();

        this.scene.popMatrix();
    }

    depositBranch(branch) {
        this.branches[this.numberOfBranches] = branch;
        this.branches[this.numberOfBranches].xCoord = 1;
        this.branches[this.numberOfBranches].yCoord = 0.5;
        this.branches[this.numberOfBranches].zCoord = 0.5;
        this.numberOfBranches++;
    }
}