/**
* MyInterface
* @constructor
*/
class MyInterface extends CGFinterface {
    constructor() {
        super();
    }

    init(application) {
        // call CGFinterface init
        super.init(application);
        // init GUI. For more information on the methods, check:
        // http://workshop.chromeexperiments.com/examples/gui
        this.gui = new dat.GUI();

        var obj = this;

        this.gui.add(this.scene, 'textures').name('Enable Textures');

        this.gui.add(this.scene, 'displayHouse').name('Display House');
        this.gui.add(this.scene, 'displaySkybox').name('Display Skybox');
        this.gui.add(this.scene, 'displayPlane').name('Display Plane');
        this.gui.add(this.scene, 'displayBird').name('Display Bird');
        this.gui.add(this.scene, 'displayNest').name('Display Nest');
        this.gui.add(this.scene, 'displayBranches').name('Display Branches');

        this.gui.add(this.scene, 'selectedTime', this.scene.dayTimes).name('Time of Day').onChange(this.scene.updateSkybox.bind(this.scene));

        this.gui.add(this.scene, 'birdScaleFactor', 0.5, 3.0).name('Bird Scale');
        this.gui.add(this.scene, 'birdSpeedFactor', 0.1, 3.0).name('Bird Speed');

        this.initKeys();
        return true;
    }

    initKeys() {
        // create reference from the scene to the GUI
        this.scene.gui = this;
        // disable the processKeyboard function
        this.processKeyboard = function () { };
        // create a named array to store which keys are being pressed
        this.activeKeys = {};
    }
    processKeyDown(event) {
        // called when a key is pressed down
        // mark it as active in the array
        this.activeKeys[event.code] = true;
    };
    processKeyUp(event) {
        // called when a key is released, mark it as inactive in the array
        this.activeKeys[event.code] = false;
    };
    isKeyPressed(keyCode) {
        // returns true if a key is marked as pressed, false otherwise
        return this.activeKeys[keyCode] || false;
    }
}