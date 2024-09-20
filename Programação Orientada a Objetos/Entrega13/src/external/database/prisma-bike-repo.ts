import { Bike } from "../../bike";
import { BikeRepo } from "../../ports/bike-repo";
import prisma from "./db"

export class PrismaBikeRepo implements BikeRepo {

    async find(id: string): Promise<Bike> {
        return await prisma.bike.findFirst({
            where: { id }
        })
    }

    async add(bike: Bike): Promise<string> {
        const addedbike = await prisma.bike.create({
            data: { ...bike }
        })
        return addedbike.id
    }

    async remove(id: string): Promise<void> {
        await prisma.bike.delete({
            where: { id }
        })
    }

    async update(id: string, bike: Bike): Promise<void> {
        const updated = await prisma.bike.update({ where: { id: id }, data: bike })
		await prisma.$transaction
    }

    async list(): Promise<Bike[]> {
        return await prisma.bike.findMany({})
    }

}