export default class ComponentBase {
    #cmodule
    #keynames

    constructor(cmodule, keynames) {
        this.#keynames = Array.isArray(keynames) ? keynames : [keynames];
        this.#cmodule = cmodule
    }
    selfRegister(keyname) {
        if(this.#cmodule.wino[keyname]!==undefined) {
            console.warn(`Already a component with keyname '${keyname}': replaced`)
        }
        this.#cmodule.wino[keyname] = this
    }
    cmodule() {
        return this.#cmodule
    }
    keynames() {
        return this.#keynames
    }
    mapNodes(dataAttrPrefix, dataAttrSuffix, action) {
        const dataAttr = this.dataAttribute(dataAttrPrefix, dataAttrSuffix)
     
        return Array.from(document.querySelectorAll(`*[${dataAttr}]`)).map(
            e => action(e, e.getAttribute(dataAttr))
        );
    }
    dataAttribute(dataAttrPrefix, dataAttrSuffix) {
        return dataAttrSuffix 
            ? `data-${dataAttrPrefix}-${dataAttrSuffix}` 
            : `data-${dataAttrPrefix}`;
    }
}