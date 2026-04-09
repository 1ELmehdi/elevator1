import ComponentBase from "./ComponentBase.js"

export default class Wino {
    #components
    #idsByKeyname = {}
    #wino_loop

    constructor(cmodule, components) {
        this.#components = components.filter(c => 
            c instanceof ComponentBase 
            || console.warn(`Must inherit ComponentBase, ignored : ${c}`
        ))
        this.#components.forEach((c, id) => c.keynames().forEach(kn => {
            if(this.#idsByKeyname[kn] != undefined) {
                console.warn(`Component ${this.#idsByKeyname[kn]} in conflict with ${id} with name ${kn}`)
            }
            this.#idsByKeyname[kn] = id
        }))
        this.#wino_loop  = async () => await cmodule.ccall('wino_loop' , undefined, [], [], { async: true })
        
        cmodule.Wino = this 
        components.forEach(c => c.beforeSetup?.());
        cmodule.ccall('wino_setup', undefined, [])
        components.forEach(c => c.afterSetup?.());
        requestAnimationFrame(() => this.loop())
    }
    async loop() {
        this.#components.forEach(c => c.beforeLoop?.());
        await this.#wino_loop()
        this.#components.forEach(c => c.afterLoop?.());
        requestAnimationFrame(() => this.loop())
    }
    idOf(keyName) {
        return this.#idsByKeyname[keyName]
    }
    byId(id) {
        return this.#components[id]  
    }
}