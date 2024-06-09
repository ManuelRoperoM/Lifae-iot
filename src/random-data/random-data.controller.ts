import { Controller, Get, Post, Body } from '@nestjs/common';
import { RandomDataService } from './random-data.service';

@Controller('random-data')
export class RandomDataController {
  constructor(private readonly randomService: RandomDataService) {}

  @Get()
  saludoRandom(): string {
    return this.randomService.getSaludo();
  }

  @Post()
  async randomNumber(@Body() body: any) {
    return await this.randomService.randomNumber(body);
  }
}
