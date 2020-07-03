class MyTreeBranch extends CGFobject {
    constructor(scene, xCoord, zCoord) {
        super(scene);
        this.branch = new MyCylinder(scene, 12);

        this.branchTexture = new CGFappearance(this.scene);
        this.branchTexture.setAmbient(0.509, 0.322, 0.004, 1);
        this.branchTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.branchTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.branchTexture.setShininess(10.0);
        this.branchTexture.loadTexture('textures/trunk.jpg');

        this.xCoord = xCoord;
        this.zCoord = zCoord;
        this.yCoord = 0.2;
        this.rotation = Math.random() * Math.PI;
    }
    initBuffers() {
        this.vertices = [];
        this.indices = [];
        this.normals = [];
        this.texCoords = [];
    }
    display() {
        this.scene.pushMatrix();

        this.scene.translate(this.xCoord, this.yCoord, this.zCoord);
        this.scene.rotate(Math.PI / 2, 0, 0, 1);
        this.scene.rotate(this.rotation, 1, 0, 0);
        this.scene.scale(0.2, 2, 0.2);
        this.branchTexture.apply();
        this.branch.display();

        this.scene.popMatrix();
    }
}
