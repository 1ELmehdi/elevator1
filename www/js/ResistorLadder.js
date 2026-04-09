import AnalogIO from "./AnalogIO.js"

export default class ResistorLadder extends AnalogIO {
    #pin
    #pullup
    
    constructor(cmodule, pin, pullup_resistor) {
        super(cmodule, pin)
        this.#pin = pin
        this.#pullup = pullup_resistor
        this.none()
    }
    resistor(r) {
        this.set(this.#pin, Math.floor((this.max() * r)/(r + this.#pullup)))
    }
    none() {
        this.set(this.#pin, this.max())
    }
}
