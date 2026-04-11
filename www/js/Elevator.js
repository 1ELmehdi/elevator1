export default class Building {
    #doors = []
    #cabin
    #position
    #columnHeight
    #columnOffsets
    #columnCount
    #floorsByColumn
    #floorCount
    #floorHeight
    #cabinOffsetX
    #cabinOffsetY
    #buildingHeight

    constructor(floorSelectors, doorSelectors, cabinSelector) {
        const floors = floorSelectors.map(sel => 
            document.querySelector(sel) 
            || console.warn(`Floor '${sel}' not found.`)
        )        
        this.#floorHeight = floors[0].offsetHeight
        this.#cabin = document.querySelector(cabinSelector)
        this.#cabinOffsetX = this.#cabin.offsetLeft
        this.#cabinOffsetY = this.#floorHeight - this.#cabin.offsetHeight - this.#cabin.offsetTop
        this.#position = this.#cabin.offsetHeight + this.#floorHeight
        this.#columnOffsets =  Array.from(new Set(
            floors.map(e => e.offsetLeft)
        )).sort((a, b) => a - b)
        this.#columnCount  = this.#columnOffsets.length
        this.#floorCount = floors.length
        this.#floorsByColumn = Math.ceil(this.#floorCount/this.#columnCount)
        this.#columnHeight = this.#floorsByColumn*this.#cabin.offsetHeight + this.#floorHeight*(this.#floorsByColumn-1)
        this.#buildingHeight = this.#columnCount*this.#columnHeight - this.#cabin.offsetHeight

        for(let i in floors) {
            const right = floors[i].querySelector(doorSelectors[1])
            const width = right.offsetWidth
            const door = {
                center: right.offsetLeft,
                width,
                left : floors[i].querySelector(doorSelectors[0]), 
                right: right,
                pos: i==this.currentFloor() ? width : 0
            }
            this.#doors.push (door)
            this.#updateDoors(door)
        }
    }
    #between = (n, min, max) => min <= n && n < max

    #updateDoors = (door) => {
        door.left.style.left  = `${door.center - door.pos - door.width}px`
        door.right.style.left = `${door.center + door.pos}px`
    }

    currentFloor() {
        return Math.floor(this.#position * this.#floorsByColumn / this.#columnHeight)
    }
    moveDoors(dir) {
        const floor = this.currentFloor()

        if(this.#between(floor, 0, this.#floorCount)) {
            const door = this.#doors[floor]
            const nextPos = door.pos - dir
            
            if(this.#between(nextPos, 0, door.width+1)) {
                door.pos = nextPos
                this.#updateDoors(door)
            }
        }
    }
    moveElevator(dir) {
        const nextPos = this.#position + dir;
        
        if(this.#between(nextPos, this.#cabin.offsetHeight, this.#buildingHeight)) {
            const left = this.#cabinOffsetX + this.#columnOffsets[Math.floor(this.#position / this.#columnHeight)]
            const top = this.#floorsByColumn * this.#floorHeight - this.#cabinOffsetY - this.#position % this.#columnHeight
            
            this.#position = nextPos; 
            this.#cabin.style.top  = `${top}px`;
            this.#cabin.style.left = `${left}px`;
        }
    }
}
