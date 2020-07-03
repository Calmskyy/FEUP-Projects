var DEGREE_TO_RAD = Math.PI / 180;
const FPS = 30;

/**
 * XMLscene class, representing the scene that is to be rendered.
 */
class XMLscene extends CGFscene {
    /**
     * @constructor
     * @param {MyInterface} myinterface 
     */
    constructor(myinterface) {
        super();

        this.interface = myinterface;
    }

    /**
     * Initializes the scene, setting some WebGL defaults, initializing the camera and the axis.
     * @param {CGFApplication} application
     */
    init(application) {
        super.init(application);

        this.sceneInited = false;

        this.enableTextures(true);

        this.viewIDs = new Object();
        this.cameraIDs = new Object();

        this.gl.clearDepth(100.0);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.enable(this.gl.CULL_FACE);
        this.gl.depthFunc(this.gl.LEQUAL);

        this.scaleFactor = 1;
        this.displayAxis = false;
        this.enableSecurityCamera = true;
        this.selectedView = 0;
        this.selectedSecurityCamera = 0;

        this.enableLight1 = false;
        this.enableLight2 = false;
        this.enableLight3 = false;
        this.enableLight4 = false;
        this.enableLight5 = false;
        this.enableLight6 = false;
        this.enableLight7 = false;
        this.enableLight8 = false;

        this.cameras = [];
        this.securityCameras = [];

        this.rtt = new CGFtextureRTT(this, this.gl.canvas.width, this.gl.canvas.height);
        this.security = new MySecurityCamera(this);

        this.axis = new CGFaxis(this);
        this.setUpdatePeriod(1000 / FPS);
    }


    /**
     * Initializes the scene cameras with the values read from the XML file.
     */
    initCameras() {
        var i = 0;
        for (var key in this.graph.cameras) {
            if (this.graph.cameras.hasOwnProperty(key)) {
                var details = this.graph.cameras[key];
                if (details.type == "perspective") {
                    var camera = new CGFcamera(details.angle, details.near, details.far, details.fromCoords, details.toCoords);
                    this.viewIDs[key] = i;
                    this.cameraIDs[key] = i;
                    this.cameras[i] = camera;
                }
                else if (details.type == "ortho") {
                    var camera = new CGFcameraOrtho(details.left, details.right, details.bottom, details.top, details.near, details.far,
                        details.fromCoords, details.toCoords, details.upCoords);
                    this.viewIDs[key] = i;
                    this.cameraIDs[key] = i;
                    this.cameras[i] = camera;
                }
            }
            i++;
        }
    }
    /**
     * Updates the scene camera used upon being changed in the interface.
     */
    updateCamera() {
        this.camera = this.cameras[this.selectedView];
    }

    /**
     * Updates the scene camera used upon being changed in the interface.
     */
    updateSecurityCamera() {
        this.securityCamera = this.cameras[this.selectedSecurityCamera];
    }

    /**
     * Updates the lights being used upon being selected in the interface.
     */
    updateLights() {
        this.enabledLights = [this.enableLight1, this.enableLight2, this.enableLight3, this.enableLight4,
        this.enableLight5, this.enableLight6, this.enableLight7, this.enableLight8];
        for (var i = 0; i < this.lights.length; i++) {
            if (this.enabledLights[i] == true) {
                this.lights[i].setVisible(true);
                this.lights[i].enable();
            }
            else {
                this.lights[i].setVisible(false);
                this.lights[i].disable();
            }
            this.lights[i].update();
        }
    }
    /**
     * Initializes the scene lights with the values read from the XML file.
     */
    initLights() {
        var i = 0;
        // Lights index.

        // Reads the lights from the scene graph.
        for (var key in this.graph.lights) {
            if (i >= 8)
                break;              // Only eight lights allowed by WebGL.

            if (this.graph.lights.hasOwnProperty(key)) {
                var light = this.graph.lights[key];

                this.lights[i].setPosition(light[2][0], light[2][1], light[2][2], light[2][3]);
                this.lights[i].setAmbient(light[3][0], light[3][1], light[3][2], light[3][3]);
                this.lights[i].setDiffuse(light[4][0], light[4][1], light[4][2], light[4][3]);
                this.lights[i].setSpecular(light[5][0], light[5][1], light[5][2], light[5][3]);

                if (light[1] == "spot") {
                    this.lights[i].setSpotCutOff(light[6]);
                    this.lights[i].setSpotExponent(light[7]);
                    this.lights[i].setSpotDirection(light[8][0], light[8][1], light[8][2]);
                }

                this.lights[i].setConstantAttenuation(light["attenuation"][0]);
                this.lights[i].setLinearAttenuation(light["attenuation"][1]);
                this.lights[i].setQuadraticAttenuation(light["attenuation"][2]);

                this.lights[i].setVisible(true);
                if (light[0]) {
                    this.lights[i].enable();
                    switch (i) {
                        case 0:
                            this.enableLight1 = true;
                            break;
                        case 1:
                            this.enableLight2 = true;
                            break;
                        case 2:
                            this.enableLight3 = true;
                            break;
                        case 3:
                            this.enableLight4 = true;
                            break;
                        case 4:
                            this.enableLight5 = true;
                            break;
                        case 5:
                            this.enableLight6 = true;
                            break;
                        case 6:
                            this.enableLight7 = true;
                            break;
                        case 7:
                            this.enableLight8 = true;
                            break;

                    }
                }
                else
                    this.lights[i].disable();

                this.lights[i].update();

                this.interface.addLight(i, key);

                i++;
            }
        }
        this.updateLights();
    }

    setDefaultAppearance() {
        this.setAmbient(0.2, 0.4, 0.8, 1.0);
        this.setDiffuse(0.2, 0.4, 0.8, 1.0);
        this.setSpecular(0.2, 0.4, 0.8, 1.0);
        this.setShininess(10.0);
    }
    /** Handler called when the graph is finally loaded. 
     * As loading is asynchronous, this may be called already after the application has started the run loop
     */
    onGraphLoaded() {
        this.axis = new CGFaxis(this, this.graph.referenceLength);

        this.gl.clearColor(this.graph.background[0], this.graph.background[1], this.graph.background[2], this.graph.background[3]);

        this.setGlobalAmbientLight(this.graph.ambient[0], this.graph.ambient[1], this.graph.ambient[2], this.graph.ambient[3]);

        this.initLights();

        this.initCameras();

        this.interface.initViews();

        this.updateCamera();

        this.updateSecurityCamera();

        this.sceneInited = true;
    }

    update(t) {
        this.checkKeys();

        if (!this.time) {
            this.time = t;
            return;
        }

        let deltaTime = t - this.time;
        this.time = t;
        if (this.sceneInited) {
            for (var key in this.graph.animations) {
                if (this.graph.animations.hasOwnProperty(key))
                    this.graph.animations[key].update(deltaTime);
            }
        }

        this.security.shader.setUniformsValues({ timeFactor: t / 100 % 1000 });
    }

    checkKeys() {
        if (this.gui.isKeyPressed("KeyM")) {
            this.graph.processMPress();
        }
    }

    /**
     * Displays the scene.
     */
    render(camera) {
        // ---- BEGIN Background, camera and axis setup
        this.interface.setActiveCamera(camera);
        this.camera = camera;

        // Clear image and depth buffer everytime we update the scene
        this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.DEPTH_BUFFER_BIT);

        // Initialize Model-View matrix as identity (no transformation
        this.updateProjectionMatrix();
        this.loadIdentity();

        // Apply transformations corresponding to the camera position relative to the origin
        this.applyViewMatrix();

        this.pushMatrix();
        if (this.displayAxis)
            this.axis.display();

        this.scale(this.scaleFactor, this.scaleFactor, this.scaleFactor);

        if (this.sceneInited) {
            // Draw axis
            this.setDefaultAppearance();

            // Displays the scene (MySceneGraph function).
            this.graph.displayScene();
        }

        this.popMatrix();
        // ---- END Background, camera and axis setup
    }

    display() {
        if (this.sceneInited) {
            if (this.enableSecurityCamera) {
                this.rtt.attachToFrameBuffer()
                this.render(this.securityCamera)
                this.rtt.detachFromFrameBuffer()
            }
            this.render(this.cameras[this.selectedView])
            if (this.enableSecurityCamera)
                this.security.display()
        }

    }
}