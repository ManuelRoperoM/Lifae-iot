import { Injectable, Logger } from '@nestjs/common';

@Injectable()
export class RandomDataService {
    private readonly logger = new Logger(RandomDataService.name);
    getSaludo(){
        return 'Hola desde random module!'
    }

    async randomNumber(data:any){
        this.logger.log(data.number);
        return 'Data recibida';
    }
}
