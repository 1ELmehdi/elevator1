import ComponentBase from "./ComponentBase.js";

export default class AnalogIO extends ComponentBase {
    #vals = []
    constructor(cmodule, pin_s) {
        const pins = Array.isArray(pin_s) ? pin_s : [ pin_s ] 

        super(cmodule, pins.map(pin => AnalogIO.pinKeyname(pin)))
        pins.forEach(pin => this.mapNodes('io', pin, (e, attrVal) => {
            const [attr, event] = attrVal.split('/')

            e.addEventListener(event, () => this.set(pin, e[attr]))
            this.set(pin, e[attr])
        }))
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
