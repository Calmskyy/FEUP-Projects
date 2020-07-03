/**
* MyInterface class, creating a GUI interface.
*/
class MyInterface extends CGFinterface {
    /**
     * @constructor
     */
    constructor() {
        super();
    }

    /**
     * Initializes the interface.
     * @param {CGFapplication} application
     */
    init(application) {
        super.init(application);
        // init GUI. For more information on the methods, check:
        //  http://workshop.chromeexperiments.com/examples/gui

        this.gui = new dat.GUI();

        this.gui.add(this.scene, 'displayAxis').name('Display Axis');

        this.gui.add(this.scene, 'scaleFactor', 0.1, 15).name('Scale Factor');

        this.initKeys();

        return true;
    }

    initKeys() {
        this.scene.gui=this;
        this.processKeyboard=function(){};
        this.activeKeys={};
    }

    processKeyDown(event) {
        this.activeKeys[event.code]=true;
    };

    processKeyUp(event) {
        this.activeKeys[event.code]=false;
    };

    isKeyPressed(keyCode) {
        return this.activeKeys[keyCode] || false;
    }
    /**
     * Initializes the view selection upon reading how many views are defined in the XML file.
     */
    initViews() {
        this.gui.add(this.scene, 'selectedView', this.scene.viewIDs).name('Selected View').onChange(this.scene.updateCamera.bind(this.scene));
        this.gui.add(this.scene, 'selectedSecurityCamera', this.scene.cameraIDs).name('Selected Camera').onChange(this.scene.updateSecurityCamera.bind(this.scene));
        this.gui.add(this.scene, 'enableSecurityCamera').name('Security Camera');
    }
    /**
     * Adds the option to enable a specific light upon reading how many lights are defined in the XML file.
     * @param i Index of the light being added.
     * @param lightName Name given to the light on the XML file.
     */
    addLight(i, lightName) {
        var variableName = 'enableLight' + (i + 1);
        this.gui.add(this.scene, variableName).name(lightName).onChange(this.scene.updateLights.bind(this.scene));
    }
}