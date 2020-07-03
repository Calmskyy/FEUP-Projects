/**
* MyScene
* @constructor
*/
class MyScene extends CGFscene {
    constructor() {
        super();
    }
    init(application) {
        super.init(application);
        this.initCameras();
        this.initLights();

        //Background color
        this.gl.clearColor(0.0, 0.0, 0.0, 1.0);

        this.gl.clearDepth(100.0);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.depthFunc(this.gl.LEQUAL);

        //Initialize scene objects
        this.groundTexCoords = [
            0, 25, 25, 25, 0, 0, 25, 0, 0, 25, 25, 25, 0, 0, 25, 0,
            0, 25, 25, 25, 0, 0, 25, 0, 0, 25, 25, 25, 0, 0, 25, 0
        ];

        this.treeGroup1 = new MyTreeGroupPatch(this);
        this.treeGroup2 = new MyTreeGroupPatch(this);
        this.treeGroup3 = new MyTreeGroupPatch(this);
        this.treeRow1 = new MyTreeRowPatch(this);
        this.treeRow2 = new MyTreeRowPatch(this);
        this.treeRow3 = new MyTreeRowPatch(this);
        this.house = new MyHouse(this);
        this.hill1 = new MyVoxelHill(this, 4);
        this.hill2 = new MyVoxelHill(this, 3);
        this.hill3 = new MyVoxelHill(this, 2);
        this.hill4 = new MyVoxelHill(this, 2);
        this.hill5 = new MyVoxelHill(this, 2);
        this.hill6 = new MyVoxelHill(this, 3);
        this.skybox = new MyCubeMap(this);
        this.ground = new MyQuad(this, this.groundTexCoords);
        this.torch = new MyTorch(this, 0);
        this.waterContainer = new MyWaterContainer(this);

        this.groundTexture = new CGFappearance(this);
        this.groundTexture.setAmbient(0.0, 0.0, 0.0, 1);
        this.groundTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.groundTexture.setSpecular(0.0, 0.0, 0.0, 1);
        this.groundTexture.setShininess(10.0);
        this.groundTexture.loadTexture('textures/grass.jpg');
        this.groundTexture.setTextureWrap('REPEAT', 'REPEAT');

        this.skyboxTexture = new CGFappearance(this);
        this.skyboxTexture.setAmbient(1, 1, 1, 1);
        this.skyboxTexture.setDiffuse(0, 0, 0, 1);
        this.skyboxTexture.setSpecular(0, 0, 0, 1);
        this.skyboxTexture.setShininess(10.0);

        this.skyboxDay = new CGFtexture(this, 'textures/skybox_day.jpg');
        this.skyboxNight = new CGFtexture(this, 'textures/skybox_night.jpg'); 

        //Objects connected to MyInterface
        this.dayTimes = { 'Day': 0, 'Night': 1 };
        this.selectedTime = 0;
        this.textures = true;
        this.displayTorch = true;
        this.displayWater = true;
        this.displayGroup = true;
        this.displayRow = true;
        this.displayHouse = true;
        this.displayHill = true;
        this.displaySkybox = true;
        this.displayGround = true;
        this.scaleFactor = 0.8;
    }
    initLights() {
        this.setGlobalAmbientLight(0.4, 0.4, 0.4, 1.0);

        this.lights[0].setPosition(20, 50, -20, 1);
        this.lights[0].setDiffuse(0.97, 0.95, 0.48, 1.0);
        this.lights[0].setConstantAttenuation(0.3);
        
        this.lights[1].setPosition(20, 50, 20, 1);
        this.lights[1].setDiffuse(0.0, 0.33, 0.65, 1.0);
        this.lights[1].setConstantAttenuation(0.4);

        this.lights[2].setPosition(-5, 5, -10, 1);
        this.lights[2].setDiffuse(1, 1, 1, 1.0);
        this.lights[2].setSpecular(0.8, 0.8, 0.8, 1.0);
    }
    initCameras() {
        this.camera = new CGFcamera(0.4, 0.1, 500, vec3.fromValues(90, 30, 20), vec3.fromValues(0, 0, 0));
    }
    setDefaultAppearance() {
        this.setAmbient(0.2, 0.4, 0.8, 1.0);
        this.setDiffuse(0.2, 0.4, 0.8, 1.0);
        this.setSpecular(0.2, 0.4, 0.8, 1.0);
        this.setShininess(10.0);
    }
    updateLights() {
        if (this.selectedTime == 0) {
            this.lights[0].enable();
            this.lights[1].disable();
            this.lights[2].disable();
            this.skyboxTexture.setTexture(this.skyboxDay);
            this.torch.updateTorch(0);
        }
        if (this.selectedTime == 1) {
            this.lights[1].enable();
            this.lights[2].enable();
            this.lights[0].disable();
            this.skyboxTexture.setTexture(this.skyboxNight);
            this.torch.updateTorch(1);
        }
        this.lights[0].update();
        this.lights[1].update();
        this.lights[2].update();
    }
    display() {
        // ---- BEGIN Background, camera and axis setup
        // Clear image and depth buffer everytime we update the scene
        this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);
        // Initialize Model-View matrix as identity (no transformation
        this.updateProjectionMatrix();
        this.loadIdentity();
        // Apply transformations corresponding to the camera position relative to the origin
        this.applyViewMatrix();

        //Apply default appearance
        this.setDefaultAppearance();

        // Scale factor
        this.scale(this.scaleFactor, this.scaleFactor, this.scaleFactor);

        // ---- BEGIN Primitive drawing section

        this.enableTextures(this.textures);

        this.updateLights();

        if (this.displayTorch) {
            this.pushMatrix();
            this.translate(-6, 0, -8);
            this.torch.display();
            this.popMatrix();
        }

        if (this.displayWater) {
            this.pushMatrix();
            this.translate(-5, 0, -22);
            this.waterContainer.display();
            this.popMatrix();
        }

        if (this.displayGroup) {
            this.pushMatrix();
            this.translate(-50, 0, 0);
            this.scale(3, 3, 3);
            this.treeGroup1.display();
            this.translate(-8, 0, 10);
            this.treeGroup2.display();
            this.translate(0, 0, -20);
            this.treeGroup3.display();
            this.popMatrix();
        }

        if (this.displayRow) {
            this.pushMatrix();
            this.translate(-25, 0, 0);
            this.scale(3, 3, 3);
            this.rotate(Math.PI / 2, 0, 1, 0);
            this.treeRow1.display();
            this.rotate(-Math.PI / 2, 0, 1, 0);
            this.translate(-4, 0, 13);
            this.treeRow2.display();
            this.translate(0, 0, -28);
            this.treeRow3.display();
            this.popMatrix();
        }

        if (this.displayHouse) {
            this.house.display();
        }

        if (this.displayHill) {
            this.pushMatrix();
            this.translate(-5, 0, 20);
            this.scale(1.5, 1.5, 1.5);
            this.hill1.display();
            this.translate(-15, 0, 5);
            this.hill2.display();
            this.translate(-10, 0, -40);
            this.hill3.display();
            this.translate(-5, 0, 0);
            this.hill4.display();
            this.translate(2, 0, -5);
            this.hill5.display();
            this.translate(25, 0, 15);
            this.hill6.display();
            this.popMatrix();
        }

        if (this.displayGround) {
            this.pushMatrix();
            this.rotate(Math.PI / 2, 0, 1, 0);
            this.rotate(Math.PI / 2, 1, 0, 0);
            this.scale(200, 200, 1);
            this.groundTexture.apply();
            this.ground.display();
            this.popMatrix();
        }

        if (this.displaySkybox) {
            this.skyboxTexture.apply();
            this.skybox.display();
        }

        // ---- END Primitive drawing section
    }
}