import ComponentBase from "./ComponentBase.js"

export default class Adafruit_7segment extends ComponentBase {
    #digits = []
    #cb

    constructor(cmodule, i2cAddr, changedCallback, dataAttrSuffix = undefined) {
        super(cmodule, `i2c/${i2cAddr}`)
        this.#cb = changedCallback
        this.mapNodes('7seg', dataAttrSuffix, (e, attrVal) => {
            let digit   = parseInt(attrVal[0])
            let segment = parseInt(attrVal[1])
            
            if(digit===NaN || segment===NaN || segment > 7) {
                console.warn(`Segment attribute 'data-7seg' has less than 2 digits, ignored ${e}`)
            }
            else {            
                this.#digits[digit] ??= { val: 0, nodes: [] }
                this.#digits[digit].nodes[segment] = e
            }
        })
        console.debug(`Adafruit_7segment on i2c address ${i2cAddr} initialized ${this.#digits.length} digits.`)
    }
    setDigits(vals) {
        for(let i in vals) {
            if(this.#digits[i]===undefined) {
                console.warn(`Try to set unknown digit ${digit} to ${val}`)
                continue
            }
            const digit = this.#digits[i]
            const val = vals[i]
            const changes = digit.val ^ val

            for(let j=0, mask=1; changes >= mask; j++, mask<<=1) {
                if(!(changes&mask))
                    continue;
                const node = digit.nodes[j]

                if(node) {
                    this.#cb(node, (val&mask)!=0)
                }
                else {
                    console.warn(`Digit ${i}, no element for segment ${j}`)
                }
            }
            this.#digits[i].val = val
        }
    }
}