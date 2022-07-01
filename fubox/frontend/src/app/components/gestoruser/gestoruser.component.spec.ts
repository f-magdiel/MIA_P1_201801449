import { ComponentFixture, TestBed } from '@angular/core/testing';

import { GestoruserComponent } from './gestoruser.component';

describe('GestoruserComponent', () => {
  let component: GestoruserComponent;
  let fixture: ComponentFixture<GestoruserComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ GestoruserComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(GestoruserComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
