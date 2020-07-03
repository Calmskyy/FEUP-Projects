class MyBird extends CGFobject {
    constructor(scene, x, y, z, xBranches, zBranches, nest) {
        super(scene);
        this.scene = scene;
        this.initBuffers();
        this.branchXCoords = xBranches;
        this.branchZCoords = zBranches;
        this.nestXCoord = -7;
        this.nestZCoord = 5;
        this.body = new MyUnitCubeQuad(this.scene);
        this.head = new MyUnitCubeQuad(this.scene);
        this.beak = new MyCone(this.scene, 4, 1);
        this.eye = new MyUnitCubeQuad(this.scene);
        this.tail = new MyCone(this.scene, 3, 1);
        this.wing = new MyWing(this.scene);

        this.bodyTexture = new CGFappearance(this.scene);
        this.bodyTexture.setAmbient(0, 0, 0, 1);
        this.bodyTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.bodyTexture.setSpecular(0, 0, 0, 1);
        this.bodyTexture.setShininess(10.0);
        this.bodyTexture.loadTexture('textures/bodyTexture.jpg');

        this.featherTexture = new CGFappearance(this.scene);
        this.featherTexture.setAmbient(0, 0, 0, 1);
        this.featherTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.featherTexture.setSpecular(0, 0, 0, 1);
        this.featherTexture.setShininess(10.0);
        this.featherTexture.loadTexture('textures/featherTexture.png');

        this.beakTexture = new CGFappearance(this.scene);
        this.beakTexture.setAmbient(0, 0, 0, 1);
        this.beakTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.beakTexture.setSpecular(0, 0, 0, 1);
        this.beakTexture.setShininess(10.0);
        this.beakTexture.loadTexture('textures/beakTexture.jpg');

        this.eyeTexture = new CGFappearance(this.scene);
        this.eyeTexture.setAmbient(0, 0, 0, 1);
        this.eyeTexture.setDiffuse(0.9, 0.9, 0.9, 1);
        this.eyeTexture.setSpecular(0, 0, 0, 1);
        this.eyeTexture.setShininess(10.0);
        this.eyeTexture.loadTexture('textures/eyeTexture.jpg');

        this.orientation = 0;
        this.speed = 0;
        this.descend = 0;
        this.xPos = x;
        this.yPos = y;
        this.zPos = z;
        this.wingAngle = 0;
        this.wingUpCycle = true;
        this.holdingBranch = false;
        this.branch = null;
        this.nest = nest;
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

        this.scene.translate(this.xPos, this.yPos, this.zPos);
        this.scene.rotate(this.orientation, 0, 1, 0);
        this.scene.translate(0, (this.scene.birdScaleFactor - 1) / 2, 0);
        this.scene.scale(this.scene.birdScaleFactor, this.scene.birdScaleFactor, this.scene.birdScaleFactor);

        this.scene.pushMatrix();

        this.scene.scale(1, 1, 1.5);

        this.bodyTexture.apply();
        this.body.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0.9, 0.5, 0);

        this.featherTexture.apply();
        this.wing.display(this.wingAngle);

        this.scene.translate(-1.8, 0, 0);
        this.scene.rotate(Math.PI, 0, 1, 0);

        this.wing.display(this.wingAngle);

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 0, -0.75);
        this.scene.rotate(- Math.PI / 2, 1, 0, 0);
        this.scene.scale(0.25, 1, 0.25);

        this.featherTexture.apply();
        this.tail.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 0.5, 0.75);

        this.bodyTexture.apply();
        this.head.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 0.5, 0.75);
        this.scene.rotate(Math.PI / 2, 1, 0, 0);
        this.scene.translate(0, 0.5, 0.2);
        this.scene.scale(0.2, 0.4, 0.2);

        this.beakTexture.apply();
        this.beak.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(1, 0.3, 1.8);
        if (this.branch != null)
            this.branch.display();

        this.scene.popMatrix();
        this.scene.pushMatrix();

        this.scene.translate(0, 0.5, 0.75);
        this.scene.rotate(Math.PI / 2, 1, 0, 0);
        this.scene.translate(0.3, 0.5, -0.2);
        this.scene.scale(0.2, 0.1, 0.2);

        this.eyeTexture.apply();
        this.eye.display();

        this.scene.translate(-3, 0, 0);

        this.eye.display();

        this.scene.popMatrix();
        this.scene.popMatrix();
    }

    turn(v) {
        this.orientation += (Math.PI / 10 * v);
    }

    accelerate(v) {
        this.speed += 0.05 * v;

        if (this.speed > 1.5)
            this.speed = 1.5;
        if (this.speed < 0)
            this.speed = 0;
    }

    startDescend() {
        if (this.descend == 0)
            this.descend = 0.225;
    }

    update(t) {

        this.xPos += this.speed * Math.sin(this.orientation);
        this.zPos += this.speed * Math.cos(this.orientation);
        this.yPos -= this.descend;

        if (this.yPos <= 0.5 * this.scene.birdScaleFactor) {
            this.yPos = 0.5 * this.scene.birdScaleFactor;
            this.descend = -0.225;
            this.groundTime = t;
        }

        if (this.descend < 0)
            if (this.yPos >= this.scene.birdStartingY) {
                this.yPos = this.scene.birdStartingY;
                this.descend = 0;
                this.groundTime = 0;
            }

        if (this.yPos == 0.5 * this.scene.birdScaleFactor) {
            if (this.holdingBranch == false) {
                for (let i = 0; i < 4; i++) {
                    if (Math.abs(this.xPos - this.branchXCoords[i]) < 2 && Math.abs(this.zPos - this.branchZCoords[i]) < 2) {
                        this.scene.getBranch(i);
                        if (this.branch != null) {
                            this.branch.xCoord = 0;
                            this.branch.yCoord = 0;
                            this.branch.zCoord = 0;
                            this.branch.rotation = 0;
                            this.holdingBranch = true;
                            break;
                        }
                    }
                }
            }
            else if (this.holdingBranch == true) {
                if (Math.abs(this.xPos - this.nestXCoord) < 2.5 && Math.abs(this.zPos - this.nestZCoord) < 2.5) {
                    this.holdingBranch = false;
                    this.nest.depositBranch(this.branch);
                    this.branch = null;
                }
            }
        }

        if (this.xPos >= 30 || this.xPos <= -30) {
            this.xPos -= this.speed * Math.sin(this.orientation);
            this.speed = 0;
        }

        if (this.zPos >= 30 || this.zPos <= -30) {
            this.zPos -= this.speed * Math.cos(this.orientation);
            this.speed = 0;
        }

        var oscilation = t % 1000;

        if (oscilation >= 0 && oscilation < 250) {
            this.yPos += 0.08 * this.scene.birdScaleFactor;
        }
        else if (oscilation >= 250 && oscilation < 750) {
            this.yPos -= 0.08 * this.scene.birdScaleFactor;
        }
        else if (oscilation >= 750 && oscilation < 1000) {
            this.yPos += 0.08 * this.scene.birdScaleFactor;
        }

        if (this.wingUpCycle)
            this.wingAngle += (Math.PI / 20 + Math.PI / 15 * this.speed);
        else
            this.wingAngle -= (Math.PI / 20 + Math.PI / 15 * this.speed);

        if (this.wingAngle >= Math.PI / 3)
            this.wingUpCycle = false;
        if (this.wingAngle <= - (Math.PI / 3))
            this.wingUpCycle = true;
    }
}