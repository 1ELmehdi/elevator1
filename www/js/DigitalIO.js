import AnalogIO from "./AnalogIO.js";

export default class DigitalIO extends AnalogIO {
    set(pin, high_low) {
        super.set(pin, high_low!==0 ? this.max():this.min())
    }
    get(pin) {
        return super.get(pin)===this.min() ? 0 : 1
    }
}