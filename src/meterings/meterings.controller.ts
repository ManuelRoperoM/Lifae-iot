import { Controller, Get, Post, Body } from '@nestjs/common';
import { MeteringsService } from './meterings.service';

@Controller('random-data')
export class MeteringsController {
  constructor(private readonly meteringsService: MeteringsService) {}

  @Get()
  saludoRandom(): string {
    return this.meteringsService.getSaludo();
  }

  @Post()
  async meteringMicroController(@Body() body: any) {
    return await this.meteringsService.calculatePowers(body);
  }

  @Post('save-metering')
  async saveMetering(@Body() body: any) {
    return await this.meteringsService.saveMetering(body);
  }

  @Get('all-meterings')
  async findAllMeterings() {
    return await this.meteringsService.findAll();
  }
}
