/**
 * MyTree
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyTree extends CGFobject {
    constructor(scene, trunkHeight, trunkRadius, treeTopHeight, treeTopRadius, trunkTexture, treeTopTexture) {
        super(scene);
        this.trunkHeight = trunkHeight;
        this.trunkRadius = trunkRadius;
        this.treeTopHeight = treeTopHeight;
        this.treeTopRadius = treeTopRadius;
        this.trunkTexture = trunkTexture;
        this.treeTopTexture = treeTopTexture;
        this.scene = scene;
        this.initBuffers();
        this.cone = new MyCone(this.scene, 8, 1);
        this.cylinder = new MyCylinder(scene, 8);

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
        this.treeTopTexture.apply();
        this.scene.scale(this.treeTopRadius*0.8, this.treeTopHeight*1.5, this.treeTopRadius*0.8);
        this.scene.translate(0, this.trunkHeight*0.8/this.treeTopHeight, 0);
        this.cone.display();
        this.scene.translate(0, this.trunkHeight*(-0.8)/this.treeTopHeight, 0);
        this.scene.scale(this.trunkRadius * 0.5/this.treeTopRadius, this.trunkHeight*0.8/this.treeTopHeight, this.trunkRadius * 0.5/this.treeTopRadius);
        this.trunkTexture.apply();
        this.cylinder.display();
        this.scene.popMatrix();
        
    }
}