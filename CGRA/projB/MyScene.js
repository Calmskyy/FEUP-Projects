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
        this.enableTextures(true);
        this.setUpdatePeriod(50);

        //Initialize scene objects
        this.axis = new CGFaxis(this);
        this.terrain = new MyTerrain(this);
        this.house = new MyHouse(this);
        this.skybox = new MyCubeMap(this);

        this.branch1X = Math.random() * 16 - 8;
        this.branch2X = Math.random() * 16 - 8;
        this.branch3X = Math.random() * 16 - 8;
        this.branch4X = Math.random() * 16 - 8;
        this.branch1Z = Math.random() * 16 - 8;
        this.branch2Z = Math.random() * 16 - 8;
        this.branch3Z = Math.random() * 16 - 8;
        this.branch4Z = Math.random() * 16 - 8;
        this.branch1 = new MyTreeBranch(this, this.branch1X, this.branch1Z);
        this.branch2 = new MyTreeBranch(this, this.branch2X, this.branch2Z);
        this.branch3 = new MyTreeBranch(this, this.branch3X, this.branch3Z);
        this.branch4 = new MyTreeBranch(this, this.branch4X, this.branch4Z);

        this.nest = new MyNest(this);

        this.treeBranches = [this.branch1, this.branch2, this.branch3, this.branch4];
        this.branchXCoords = [this.branch1X, this.branch2X, this.branch3X, this.branch4X];
        this.branchYCoords = [this.branch1Z, this.branch2Z, this.branch3Z, this.branch4Z];

        this.birdStartingX = 5;
        this.birdStartingY = 5;
        this.birdStartingZ = 5;
        this.bird = new MyBird(this, this.birdStartingX, this.birdStartingY, this.birdStartingZ, this.branchXCoords, this.branchYCoords, this.nest);

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
        this.displayPlane = true;
        this.displayHouse = true;
        this.displaySkybox = true;
        this.displayBird = true;
        this.displayNest = true;
        this.displayBranches = true;
        this.updateSkybox();
        this.textures = true;
        this.birdScaleFactor = 1;
        this.birdSpeedFactor = 0.5;
        this.axiom = "X";
        this.ruleF = "FF";
        this.ruleX = "F[-X][X]F[-X]+FX";
        this.angle = 25.0;
        this.iterations = 3;
        this.scaleFactor = 0.5;
        this.lSystem = new MyLightning(this);

        this.doGenerate = function () {
            this.lSystem.generate(
                this.axiom,
                {
                    "F": [this.ruleF],
                    "X": [this.ruleX]
                },
                this.angle,
                this.iterations,
                this.scaleFactor
            );
        }

        // do initial generation
        this.doGenerate();

        //Initialize scene objects
        this.axis = new CGFaxis(this);
    }
    initLights() {
        this.lights[0].setPosition(15, 2, 5, 1);
        this.lights[0].setDiffuse(1.0, 1.0, 1.0, 1.0);
        this.lights[0].enable();
        this.lights[0].update();
    }
    initCameras() {
        this.camera = new CGFcamera(0.4, 0.1, 500, vec3.fromValues(45, 45, 45), vec3.fromValues(0, 0, 0));
    }
    setDefaultAppearance() {
        this.setAmbient(0.2, 0.4, 0.8, 1.0);
        this.setDiffuse(0.2, 0.4, 0.8, 1.0);
        this.setSpecular(0.2, 0.4, 0.8, 1.0);
        this.setShininess(10.0);
    }
    updateSkybox() {
        if (this.selectedTime == 0) {
            this.skyboxTexture.setTexture(this.skyboxDay);
        }
        if (this.selectedTime == 1) {
            this.skyboxTexture.setTexture(this.skyboxNight);
        }
    }
    checkKeys() {
        // Check for key codes e.g. in https://keycode.info/
        var movementPressed = false;

        if (this.gui.isKeyPressed("KeyW")) {
            this.bird.accelerate(this.birdSpeedFactor);
            movementPressed = true;
        }
        if (this.gui.isKeyPressed("KeyS")) {
            this.bird.accelerate(-this.birdSpeedFactor);
            movementPressed = true;
        }
        if (this.gui.isKeyPressed("KeyA")) {
            this.bird.turn(this.birdSpeedFactor);
        }
        if (this.gui.isKeyPressed("KeyD")) {
            this.bird.turn(-this.birdSpeedFactor);
        }
        if (this.gui.isKeyPressed("KeyR")) {
            this.bird.xPos = this.birdStartingX;
            this.bird.yPos = this.birdStartingY;
            this.bird.zPos = this.birdStartingZ;
            this.bird.orientation = 0;
            this.bird.speed = 0;
        }
        if (this.gui.isKeyPressed("KeyP")) {
            this.bird.startDescend();
        }
        if (this.gui.isKeyPressed("KeyL")) {
            this.moveLightningX = Math.random() * 25 - 15;
            this.moveLightningZ = Math.random() * 25 - 15;

            this.displayLightning = true;
        }
        if (movementPressed == false)
            this.bird.accelerate(-this.birdSpeedFactor / 5);
    }

    update(t) {
        this.checkKeys();
        this.bird.update(t);
    }

    getBranch(i) {
        this.bird.branch = this.treeBranches[i];
        this.treeBranches[i] = null;
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

        // Draw axis
        this.axis.display();

        //Apply default appearance
        this.setDefaultAppearance();

        // ---- BEGIN Primitive drawing section
        this.enableTextures(this.textures);

        //  Terrain
        if (this.displayPlane) {
            this.pushMatrix();
            this.rotate(-0.5 * Math.PI, 1, 0, 0);
            this.scale(60, 60, 1);
            this.terrain.display();
            this.popMatrix();
            this.setActiveShader(this.defaultShader);
        }

        //  House
        if (this.displayHouse) {
            this.pushMatrix();
            this.translate(-3, 0, -3);
            this.house.display();
            this.popMatrix();
        }

        //  Bird
        if (this.displayBird) {
            this.bird.display();
        }

        //  Skybox
        if (this.displaySkybox) {
            this.skyboxTexture.apply();
            this.skybox.display();
        }

        //  Branches
        if (this.displayBranches) {
            for (let i = 0; i < 4; i++)
                if (this.treeBranches[i] != null)
                    this.treeBranches[i].display();
        }

        //  Nest
        if (this.displayNest) {
            this.pushMatrix();
            this.translate(-7, 0, 5);
            this.nest.display();
            this.popMatrix();
        }

        // Lightning
        if (this.displayLightning) {
            this.pushMatrix();
            this.rotate(Math.PI, 1, 0, 0);
            this.translate(this.moveLightningX, -10, this.moveLightningZ);
            this.lSystem.display();
            this.popMatrix();
        }

        // ---- END Primitive drawing section
    }
}