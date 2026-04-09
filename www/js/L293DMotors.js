import DigitalIO from "./DigitalIO.js";

export default class L293DMotors extends DigitalIO {
    #motors = []

    constructor(cmodule, pins, motor1Callback, motor2Callback) {
        super(cmodule, pins)
        if(!Array.isArray(pins)||(pins.length < 4)) {
            console.error(`Bad L239DMotors pins : must be an array of 4 int`)
        }
        for(let i = 0; i<4; i+=2) {
            this.#motors.push({
                cb: i ? motor2Callback : motor1Callback,
                pins: pins.slice(i, i+2)
            })
        }     
    }
    afterLoop() {
        for(let m of this.#motors) {
            m.cb(this.get(m.pins[0]) - this.get(m.pins[1]));
        }
    }
}