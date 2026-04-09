import ComponentBase from "./ComponentBase.js";

export default class AnalogIO extends ComponentBase {
    #vals = []
    constructor(cmodule, pin_s) {
        super(cmodule, Array.isArray(pin_s) 
            ? pin_s.map(pin => AnalogIO.pinKeyname(pin))
            : AnalogIO.pinKeyname(pin_s)
        )
    }
    static pinKeyname(pin) {
        return `io/${pin}`
    }
    set(pin, val) {
        this.#vals[pin] = val
    }
    get(pin) {
        return this.#vals[pin] ?? 0
    }
    min() { return 0 }
    max() { return 1023 }
}
