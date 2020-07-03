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

        //Checkbox element in GUI
        this.gui.add(this.scene, 'textures').name('Enable Textures');
        this.gui.add(this.scene, 'displayTorch').name('Display Torch');
        this.gui.add(this.scene, 'displayWater').name('Display Pond');
        this.gui.add(this.scene, 'displayGroup').name('Display Group');
        this.gui.add(this.scene, 'displayRow').name('Display Row');
        this.gui.add(this.scene, 'displayHouse').name('Display House');
        this.gui.add(this.scene, 'displayHill').name('Display Hill');
        this.gui.add(this.scene, 'displaySkybox').name('Display Skybox');
        this.gui.add(this.scene, 'displayGround').name('Display Ground');

        this.gui.add(this.scene, 'selectedTime', this.scene.dayTimes).name('Time of Day').onChange(this.scene.updateLights.bind(this.scene));
        
        this.gui.add(this.scene, 'scaleFactor', 0.1, 10.0).name('Scale');

        //this.gui.add(this.scene, 'objectComplexity', 0.01, 1.0).onChange(this.scene.updateObjectComplexity.bind(this.scene));

        return true;
    }
}