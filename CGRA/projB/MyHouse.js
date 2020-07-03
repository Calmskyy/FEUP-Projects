/**
 * MyHouse
 * @constructor
 * @param scene - Reference to MyScene object
 */
class MyHouse extends CGFobject {
    constructor(scene) {
        super(scene);
        this.initBuffers();
        this.firstFloor = new MyUnitCubeQuad(scene);
        this.secondFloor = new MyUnitCubeQuad(scene);
        this.floorSeparator = new MyUnitCubeQuad(scene);
        this.pyramidRoof = new MyPyramid(scene, 4, 4);
        this.solarPanelPipe = new MyPrism(scene, 3);
        this.solarPanel = new MyQuad(scene);
        this.column1 = new MyPrism(scene, 6);
        this.column2 = new MyPrism(scene, 6);
        this.column3 = new MyPrism(scene, 6);
        this.column4 = new MyPrism(scene, 6);
        this.door = new MyQuad(scene);
        this.window = new MyQuad(scene);

        var pathCoords = [
			0, 1,
			0.125, 1,
			0, 0,
			0.125, 0,
			0, 1,
			0.125, 1,
			0, 0,
			0.125, 0
        ]
        
        this.path = new MyQuad(scene, pathCoords);
        this.scene = scene;

        this.columnTexture = new CGFappearance(this.scene);
        this.columnTexture.setAmbient(0, 0, 0, 1);
        this.columnTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.columnTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.columnTexture.setShininess(10.0);
        this.columnTexture.loadTexture('textures/cement.jpg');

        this.pipeMaterial = new CGFappearance(this.scene);
        this.pipeMaterial.setAmbient(0.4, 0.4, 0.4, 1);
        this.pipeMaterial.setDiffuse(0.4, 0.4, 0.4, 1);
        this.pipeMaterial.setSpecular(0.4, 0.4, 0.4, 1);
        this.pipeMaterial.setShininess(10.0);
        this.pipeMaterial.loadTexture('textures/pipe.jpg');

        this.doorTexture = new CGFappearance(this.scene);
        this.doorTexture.setAmbient(0.1, 0.1, 0.1, 1);
        this.doorTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.doorTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.doorTexture.setShininess(10.0);
        this.doorTexture.loadTexture('textures/door.png');

        this.windowTexture = new CGFappearance(this.scene);
        this.windowTexture.setAmbient(0.1, 0.1, 0.1, 1);
        this.windowTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.windowTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.windowTexture.setShininess(10.0);
        this.windowTexture.loadTexture('textures/window.png');

        this.panelTexture = new CGFappearance(this.scene);
        this.panelTexture.setAmbient(0.1, 0.1, 0.1, 1);
        this.panelTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.panelTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.panelTexture.setShininess(10.0);
        this.panelTexture.loadTexture('textures/solarPanel.jpg');

        this.wallTexture = new CGFappearance(this.scene);
        this.wallTexture.setAmbient(0.1, 0.1, 0.1, 1);
        this.wallTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.wallTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.wallTexture.setShininess(10.0);
        this.wallTexture.loadTexture('textures/brick.jpg');

        this.roofTexture = new CGFappearance(this.scene);
        this.roofTexture.setAmbient(0, 0, 0, 1);
        this.roofTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.roofTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.roofTexture.setShininess(10.0);
        this.roofTexture.loadTexture('textures/roof.jpg');

        this.pathTexture = new CGFappearance(this.scene);
        this.pathTexture.setAmbient(0.1, 0.1, 0.1, 1);
        this.pathTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.pathTexture.setSpecular(0.1, 0.1, 0.1, 1);
        this.pathTexture.setShininess(10.0);
        this.pathTexture.loadTexture('textures/path.png');
        this.pathTexture.setTextureWrap('REPEAT', 'REPEAT');

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

        this.scene.translate(0, 0.75, 0);
        this.scene.scale(1.5, 1.5, 1.5);
        this.wallTexture.apply();
        this.firstFloor.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.scale(3, 0.25, 3);
        this.scene.translate(0, 6.5, 0);
        this.roofTexture.apply();
        this.floorSeparator.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 3, 0);
        this.scene.scale(2, 2.5, 2);
        this.wallTexture.apply();
        this.secondFloor.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(-0.9, 3, 0);
        this.scene.scale(1.5, 1.5, 1.5);
        this.scene.rotate(Math.PI / 4, 0, 0, 1);
        this.scene.scale(0.1, 1, 0.1);
        this.pipeMaterial.apply();
        this.solarPanelPipe.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(-2.025, 4.01, 0);
        this.scene.rotate(- Math.PI / 2, 0, 1, 0);
        this.scene.rotate(- Math.PI / 4, 1, 0, 0);
        this.scene.scale(1.5, 1.5, 1.5);
        this.panelTexture.apply();
        this.solarPanel.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 4.25, 0);
        this.scene.scale(1.5, 1.5, 1.5);
        this.scene.rotate(Math.PI / 4, 0, 1, 0);
        this.roofTexture.apply();
        this.pyramidRoof.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(1.01, 2.5, 0.5);
        this.scene.scale(0.5, 0.5, 0.5);
        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.windowTexture.apply();
        this.window.display();
        this.scene.translate(2, 0, 0);
        this.window.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.doorTexture.apply();
        this.scene.translate(0.76, 0.325, 0);
        this.scene.scale(0.35, 0.65, 0.35);
        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.door.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.columnTexture.apply();

        this.scene.translate(1.25, 0, 1.25);
        this.scene.scale(0.25, 1.5, 0.25);
        this.column1.display();

        this.scene.translate(-10, 0, 0);
        this.column2.display();

        this.scene.translate(0, 0, -10);
        this.column3.display();

        this.scene.translate(10, 0, 0);
        this.column4.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(2.25, 0.01, 0);
        this.scene.rotate(Math.PI / 2, 0, 1, 0);
        this.scene.rotate(Math.PI / 2, 1, 0, 0);
        this.scene.scale(0.5, 3, 0.5);
        this.pathTexture.apply();
        this.path.display();

        this.scene.popMatrix();
    }
}