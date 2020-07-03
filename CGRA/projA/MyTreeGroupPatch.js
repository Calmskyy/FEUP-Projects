/**
 * MyTreeGroupPatch
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyTreeGroupPatch extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initBuffers();
        this.scene = scene;

        this.xTranslate1 = Math.random();
        this.xTranslate2 = Math.random();
        this.xTranslate3 = Math.random();
        this.xTranslate4 = Math.random();
        this.xTranslate5 = Math.random();
        this.xTranslate6 = Math.random();
        this.xTranslate7 = Math.random();
        this.xTranslate8 = Math.random();

        this.zTranslate1 = Math.random();
        this.zTranslate2 = Math.random();
        this.zTranslate3 = Math.random();
        this.zTranslate4 = Math.random();
        this.zTranslate5 = Math.random();
        this.zTranslate6 = Math.random();
        this.zTranslate7 = Math.random();
        this.zTranslate8 = Math.random();

        this.trunkTexture = new CGFappearance(this.scene);
        this.trunkTexture.setAmbient(0, 0, 0, 1);
        this.trunkTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.trunkTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.trunkTexture.setShininess(10.0);
        this.trunkTexture.loadTexture('textures/trunk.jpg');

        this.treeTopTexture = new CGFappearance(this.scene);
        this.treeTopTexture.setAmbient(0, 0, 0, 1);
        this.treeTopTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.treeTopTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.treeTopTexture.setShininess(10.0);
        this.treeTopTexture.loadTexture('textures/treeTop.jpg');

        this.tree1 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree2 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree3 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree4 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree5 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree6 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree7 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree8 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
        this.tree9 = new MyTree(scene, 0.9 + Math.random(), 0.5 + Math.random(), 0.5 + Math.random(), 0.7 + Math.random(), this.trunkTexture, this.treeTopTexture);
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

        this.tree1.display();

        this.scene.translate(-1.5 - this.xTranslate1, 0, -0.5 + this.zTranslate1);
        this.tree2.display();

        this.scene.translate(-0.5 + this.xTranslate2, 0, 1.5 + this.zTranslate2);
        this.tree3.display();

        this.scene.translate(-0.5 + this.xTranslate3, 0, -3.5 - this.zTranslate3);
        this.tree4.display();

        this.scene.translate(3.5 + this.xTranslate4, 0, -0.5 + this.zTranslate4);
        this.tree5.display();

        this.scene.translate(-0.5 + this.xTranslate5, 0, 1.5 + this.zTranslate5);
        this.tree6.display();

        this.scene.translate(-0.5 + this.xTranslate6, 0, 1.5 + this.zTranslate6);
        this.tree7.display();

        this.scene.translate(-2 - this.xTranslate7, 0, -0.5 + this.zTranslate7);
        this.tree8.display();

        this.scene.translate(-0.5 + this.xTranslate8, 0, -3.5 - this.zTranslate8);
        this.tree9.display();

        this.scene.popMatrix();
    }
}